#ifndef __FIRSTPERSONCAMERA_H__
#define __FIRSTPERSONCAMERA_H__

#include "Camera.h"

// First person camera. Moves relative to the forward direction and vertical angle limited to 85 degrees.
class FirstPersonCamera : public Camera {
	public:
		// Move the current position by an offset, relative to the looking direction.
		virtual void move(const glm::vec3& offset);

		// Set angles by an offset (in degrees). Vertical angle limited to 85 degrees.
		virtual void rotate(float horizontalAngle, float verticalAngle, float tiltAngle);

		// The direction in which the camera is currently facing.
		glm::vec3 forward() const;

		// The direction representing the direction to the right of the camera.
		glm::vec3 right() const;

		// The camera's up-vector.
		glm::vec3 up() const;
};

#endif