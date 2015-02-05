#include "ParticleSystem.h"
#include <vector>

ParticleSystem::ParticleSystem(glm::vec3 origin, int maxParticleCount, int chanceToEmit, float maxVelocity, float maxLifeTime) {
	particleOrigin = origin;
	this->maxParticleCount = maxParticleCount;
	this->chanceToEmit = chanceToEmit;
	this->maxVelocity = maxVelocity;
	this->maxLifeTime = maxLifeTime;
	particleCount = 0;
}

unsigned int ParticleSystem::getParticleCount() {
	return particleCount;
}

unsigned int ParticleSystem::getMaxParticleCount() {
	return maxParticleCount;
}

ParticleSystem::ParticlePosition* ParticleSystem::getStartAddress() {
	return &this->particlePositions[0];
}

void ParticleSystem::emitParticle() {
	if ((rand() % 1000 + 1 <= chanceToEmit) && (particleCount < maxParticleCount)) {
		ParticlePosition newVertex;
		ParticleProperty newProperty;
		float xVel, yVel, zVel;
		
		newVertex.worldPos = particleOrigin;
		newProperty.lifetime = 0;
		xVel = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));
		yVel = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));
		zVel = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));
		newProperty.velocity = glm::vec3(xVel,yVel, zVel);

		particlePositions.push_back(newVertex);
		particleProperties.push_back(newProperty);

		particleCount++;
	}
}

void ParticleSystem::update(double time) {
	if (!this->particlePositions.empty()) {
		for (std::vector<int>::size_type i = 0; i != particleProperties.size(); i++) {
			if (particleProperties[i].lifetime > maxLifeTime) {
				particlePositions.erase(particlePositions.begin() + i);
				particleProperties.erase(particleProperties.begin() + i);
				particleCount--;
				i--;
			} else {
				particlePositions[i].worldPos += static_cast<float>(time)* particleProperties[i].velocity;
				particleProperties[i].lifetime += static_cast<float>(time);
			}
		}
	}
	emitParticle();
}