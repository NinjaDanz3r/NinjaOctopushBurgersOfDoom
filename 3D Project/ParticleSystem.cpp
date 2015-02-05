#include "ParticleSystem.h"
#include <vector>

ParticleSystem::ParticleSystem(glm::vec3 origin, int maxParticleCount, int chanceToEmit, float maxVelocity, float maxLifeTime) {
	this->particleOrigin = origin;
	this->maxParticleCount = maxParticleCount;
	this->chanceToEmit = chanceToEmit;
	this->maxVelocity = maxVelocity;
	this->maxLifeTime = maxLifeTime;
	this->particleCount = 0;
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

		this->particlePositions.push_back(newVertex);
		this->particleProperties.push_back(newProperty);

		particleCount++;
	}
}

void ParticleSystem::update(double time) {
	if (!this->particlePositions.empty()) {
		for (std::vector<int>::size_type i = 0; i != this->particleProperties.size(); i++) {
			if (this->particleProperties[i].lifetime > maxLifeTime) {
				this->particlePositions.erase(particlePositions.begin() + i);
				this->particleProperties.erase(particleProperties.begin() + i);
				particleCount--;
				i--;
			} else {
				this->particlePositions[i].worldPos += static_cast<float>(time)* (this->particleProperties[i].velocity);
				this->particleProperties[i].lifetime += static_cast<float>(time);
			}
		}
	}
	emitParticle();
}