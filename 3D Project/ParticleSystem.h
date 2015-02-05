#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__
#include <vector>
#include <glm\glm.hpp>

//Emitter Controller
class ParticleSystem
{
public:
	//Ordered pair of values, each particle has vertex that corresponds to a property.
	struct Vertex
	{
		glm::vec3 worldPos;
	};
	struct ParticleProperty
	{
		glm::vec3 velocity;
		float lifetime;
	};
	//Constructors
	ParticleSystem();
	ParticleSystem(glm::vec3 origin, int maxParticleCount, int chanceToEmit, float maxVelocity, float maxLifeTime);
	//Destructor
	~ParticleSystem();

	unsigned int getParticleCount();
	unsigned int getMaxParticleCount();
	void update(double time);
	Vertex* getStartAddress();
private:
	std::vector < Vertex > vertices;
	std::vector < ParticleProperty > particleProperties;
	
	//Properties of the system
	glm::vec3 particleOrigin;
	unsigned int particleCount;
	unsigned int maxParticleCount;
	float maxLifeTime;
	float maxVelocity;
	int chanceToEmit;
	//Helper functions
	void emitParticle();
};

#endif