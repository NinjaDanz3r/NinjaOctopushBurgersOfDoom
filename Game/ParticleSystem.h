#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class ShaderProgram;
class Texture;
class Camera;

/** @ingroup game
 * @{
 */

/// Handles particles.
class ParticleSystem {
	public:
		/// A particle's position in the world.
		struct ParticlePosition {
			/// Position.
			glm::vec3 worldPos;
			/// Alpha.
			float alpha;
		};
		
		/// A particle's properties.
		struct ParticleProperty {
			/// Velocity.
			glm::vec3 velocity;
			/// Lifetime (in seconds).
			float lifetime;
		};

		/// Create a new particle system with the given properties.
		/**
		 * @param shaderProgram ShaderProgram used to render the particles.
		 * @param texture Texture to apply to the particles.
		 * @param origin Origin of the particle system.
		 * @param maxParticleCount The maximum amount of particles the particle system can hold.
		 * @param chanceToEmit How large chance to emit a particle each step (x in 1000 chance).
		 * @param maxVelocity Maximum velocity of the particles emitted.
		 * @param maxLifeTime Maximum lifetime of the particles emitted.
		 */
		ParticleSystem(ShaderProgram* shaderProgram, Texture* texture, glm::vec3 origin, int maxParticleCount, int chanceToEmit, float maxVelocity, float maxLifeTime);

		/// Destructor.
		~ParticleSystem();

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

		/// Render particles.
		/**
		 * @param width Width of the context.
		 * @param height Height of the context.
		 * @param camera Camera through which to render.
		 */
		void render(int width, int height, const Camera* camera);

	private:
		// Helper functions
		void bindPointData();
		void emitParticle();

		ShaderProgram* shaderProgram;
		Texture* texture;

		std::vector<ParticlePosition> particlePositions;
		std::vector<ParticleProperty> particleProperties;
	
		// System properties
		glm::vec3 particleOrigin;
		unsigned int particleCount;
		unsigned int maxParticleCount;
		float maxLifeTime;
		float maxVelocity;
		int chanceToEmit;

		// Vertex buffer.
		GLuint vertexBuffer = 0;
		GLuint vertexAttribute = 0;
		unsigned int vertexCount = 0;
};

/** @} */

#endif