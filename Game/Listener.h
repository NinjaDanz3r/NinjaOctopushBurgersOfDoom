#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <glm/glm.hpp>

/** @ingroup game
 * @{
 */

/// Wrapper for OpenAL listener.
/**
 * 3D Sounds are played in relation to the listener's position. Does not need to be created as it is automatically created by the SoundSystem.
 */
class Listener {
	public:
		/// Get position.
		/**
		 * Starting position: (0.0, 0.0, 0.0).
		 * @return The listener's position in the game world
		 */
		const glm::vec3& position() const;

		/// Set position.
		/**
		 * @param position The listener's new position.
		 */
		void setPosition(const glm::vec3& position);

		/// Get the direction the listener is facing.
		/**
		 * @return The direction in which the listener is currently facing
		 */
		const glm::vec3& forward() const;

		/// Get the listener's up-vector.
		/**
		 * @return The listener's up-vector
		 */
		const glm::vec3& up() const;

		/// Set orientation.
		/**
		 * @param forward The direction the listener is facing.
		 * @param up The listener's up-vector.
		 */
		void setOrientation(glm::vec3& forward, glm::vec3& up);

	private:
		glm::vec3 _position = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 _forward = glm::vec3(0.f, 0.f, -1.f);
		glm::vec3 _up = glm::vec3(0.f, 1.f, 0.f);

		float _horizontalAngle = 0.f;
		float _verticalAngle = 0.f;
		float _tiltAngle = 0.f;
};

/** @} */

#endif