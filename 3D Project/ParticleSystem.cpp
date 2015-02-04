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

int ParticleSystem::getMaxParticleCount()
{
	return maxParticleCount;
}

void ParticleSystem::emitParticle()
{
	if ( (rand() % 100 + 1 <= chanceToEmit) && (particleCount < maxParticleCount))
	{
		Vertex newVertex;
		ParticleProperty newProperty;
		float xVel, yVel, zVel;
		
		newVertex.worldPos = particleOrigin;
		newProperty.lifetime = 0;
		xVel = rand() % (2 * int(maxVelocity)) - int(maxVelocity);
		yVel = rand() % (2 * int(maxVelocity)) - int(maxVelocity);
		zVel = rand() % (2 * int(maxVelocity)) - int(maxVelocity);
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