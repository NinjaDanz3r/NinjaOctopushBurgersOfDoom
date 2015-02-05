#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__
#include <vector>
#include <glm\glm.hpp>

/// Summary
/**
* Creates particles
*/
class ParticleSystem
{
public:
	/// Summary
	/**
	* Describes vertex properties
	*/
	struct Vertex
	{
		glm::vec3 worldPos;
	};
	/// Summary
	/**
	* Describes particle properties
	*/
	struct ParticleProperty
	{
		glm::vec3 velocity;
		float lifetime;
	};
	/// Summary
	/**
	* Default constructor (Not in use)
	*/
	ParticleSystem();
	/// Summary
	/**
	* param glm::vec3 origin, int maxParticleCount, int chanceToEmit (x in 1000 chance), float maxVelocity, float maxLifeTime.
	*/
	ParticleSystem(glm::vec3 origin, int maxParticleCount, int chanceToEmit, float maxVelocity, float maxLifeTime);
	/// Summary
	/**
	* Destructor
	*/
	~ParticleSystem();

	/// Summary
	/**
	* @return How many particles currently exist.
	*/
	unsigned int getParticleCount();
	/// Summary
	/**
	* @return Maximum amount of particles.
	*/
	unsigned int getMaxParticleCount();
	/// Summary
	/**
	* Updates the system.
	*/
	void update(double time);
	/// Summary
	/**
	* Returns the address to the dynamic array that holds the vertices.
	*/
	Vertex* getStartAddress();
private:
	std::vector < Vertex > vertices;
	std::vector < ParticleProperty > particleProperties;
	
	//System properties
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