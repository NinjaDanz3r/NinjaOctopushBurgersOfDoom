#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__
#include <vector>
#include <glm\glm.hpp>

/// Handles particles.
class ParticleSystem
{
public:
	/// A particle's position in the world.
	struct ParticlePosition
	{
		/// Position.
		glm::vec3 worldPos;
	};
	/// A particle's properties.
	struct ParticleProperty
	{
		/// Velocity.
		glm::vec3 velocity;
		/// Lifetime (in seconds).
		float lifetime;
	};

	/// Create a new particle system with the given properties.
	/**
	* @param origin Origin of the particle system.
	* @param maxParticleCount The maximum amount of particles the particle system can hold.
	* @param chanceToEmit How large chance to emit a particle each step (x in 1000 chance).
	* @param maxVelocity Maximum velocity of the particles emitted.
	* @param maxLifeTime Maximum lifetime of the particles emitted.
	*/
	ParticleSystem(glm::vec3 origin, int maxParticleCount, int chanceToEmit, float maxVelocity, float maxLifeTime);

	/// Get the amount of particles.
	/**
	* @return How many particles currently exist.
	*/
	unsigned int getParticleCount();

	/// Get the maximum amount of particles.
	/**
	* @return Maximum amount of particles.
	*/
	unsigned int getMaxParticleCount();

	/// Update all the system's particles, spawn new particles etc.
	/**
	 * @param time Time since last frame (in seconds).
	 */
	void update(double time);

	/// Get the address to the dynamic array that holds the particle positions.
	/**
	* @return The address to the dynamic array that holds the particle positions
	*/
	ParticlePosition* getStartAddress();
private:
	std::vector<ParticlePosition> particlePositions;
	std::vector<ParticleProperty> particleProperties;
	
	// System properties
	glm::vec3 particleOrigin;
	unsigned int particleCount;
	unsigned int maxParticleCount;
	float maxLifeTime;
	float maxVelocity;
	int chanceToEmit;

	// Helper functions
	void emitParticle();
};

#endif