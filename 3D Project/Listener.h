#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <glm/glm.hpp>

class Listener {
	public:
		// Get position.
		const glm::vec3& position() const;

		// Set position.
		void setPosition(const glm::vec3& position);

		// The direction in which the listener is currently facing.
		const glm::vec3& forward() const;

		// The listener's up-vector.
		const glm::vec3& up() const;

		// Set orientation.
		void setOrientation(glm::vec3& forward, glm::vec3& up);

	private:
		glm::vec3 _position = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 _forward = glm::vec3(0.f, 0.f, -1.f);
		glm::vec3 _up = glm::vec3(0.f, 1.f, 0.f);

		float _horizontalAngle = 0.f;
		float _verticalAngle = 0.f;
		float _tiltAngle = 0.f;
};

#endif