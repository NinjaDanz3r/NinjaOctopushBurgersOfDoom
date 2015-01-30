#include "ParticleSystem.h"
#include "ParticleEmitter.h"
#include <vector>

ParticleSystem::ParticleSystem()
{

}

ParticleSystem::~ParticleSystem()
{

}

int ParticleSystem::getParticleCount()
{
	return particleCount;
}

void createEmitter(const char* texturePath, glm::vec3 worldPos)
{

}