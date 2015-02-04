#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__
#include "ParticleEmitter.h"
#include <vector>
#include <glm\glm.hpp>

//Emitter Controller
class ParticleSystem
{
public:
	//Constructor
	ParticleSystem();
	//Destructor
	~ParticleSystem();

	int getParticleCount();
	int getMaxParticleCount();
	void update(double time);
private:
	//Ordered pair of values, each particle has a property.
	struct Vertex
	{
		glm::vec3 worldPos;
	};
	struct ParticleProperty
	{
		glm::vec3 velocity;
		float lifetime;
	};

	std::vector < Vertex > vertices;
	std::vector < ParticleProperty > particleProperties;
	
	//Properties of the system
	glm::vec3 particleOrigin;
	int particleCount;
	int maxParticleCount;
	float maxLifeTime;
	float maxVelocity;
	int chanceToEmit;
	//Helper functions
	void emitParticle();
};

#endif