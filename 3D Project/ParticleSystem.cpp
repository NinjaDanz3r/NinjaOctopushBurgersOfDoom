#include "ParticleSystem.h"
#include <vector>

ParticleSystem::ParticleSystem()
{

}

ParticleSystem::~ParticleSystem()
{

}

ParticleSystem::ParticleSystem(glm::vec3 origin, int maxParticleCount, int chanceToEmit, float maxVelocity, float maxLifeTime)
{
	this->particleOrigin = origin;
	this->maxParticleCount = maxParticleCount;
	this->chanceToEmit = chanceToEmit;
	this->maxVelocity = maxVelocity;
	this->maxLifeTime = maxLifeTime;
	this->particleCount = 0;
}

unsigned int ParticleSystem::getParticleCount()
{
	return particleCount;
}

unsigned int ParticleSystem::getMaxParticleCount()
{
	return maxParticleCount;
}

ParticleSystem::Vertex* ParticleSystem::getStartAddress()
{
	return &this->vertices[0];
}

void ParticleSystem::emitParticle()
{
	if ( (rand() % 1000 + 1 <= chanceToEmit) && (particleCount < maxParticleCount))
	{
		Vertex newVertex;
		ParticleProperty newProperty;
		float xVel, yVel, zVel;
		
		newVertex.worldPos = particleOrigin;
		newProperty.lifetime = 0;
		xVel = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));
		yVel = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));
		zVel = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));
		newProperty.velocity = glm::vec3(xVel,yVel, zVel);

		this->vertices.push_back(newVertex);
		this->particleProperties.push_back(newProperty);

		particleCount++;
	}
}

void ParticleSystem::update(double time)
{
	if (!this->vertices.empty())
	{
		for (std::vector<int>::size_type i = 0; i != this->particleProperties.size(); i++)
		{
			if (this->particleProperties[i].lifetime > maxLifeTime)
			{
				this->vertices.erase(vertices.begin()+i);
				this->particleProperties.erase(particleProperties.begin() + i);
				particleCount--;
				i--;
			}
			else
			{
				this->vertices[i].worldPos += float(time) * (this->particleProperties[i].velocity); 
				this->particleProperties[i].lifetime += float(time);
			}
		}
	}
	emitParticle();
}