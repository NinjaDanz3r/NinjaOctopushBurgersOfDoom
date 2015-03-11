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
	if ((rand() % 1000 < chanceToEmit) && (particleCount < maxParticleCount)) {
		ParticlePosition newPosition;
		ParticleProperty newProperty;
		
		newPosition.worldPos = particleOrigin;
		newProperty.lifetime = 0.f - static_cast<float>(rand()%static_cast<int>(maxLifeTime*2));
		newProperty.velocity.x = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));
		newProperty.velocity.y = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));
		newProperty.velocity.z = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));

		particlePositions.push_back(newPosition);
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