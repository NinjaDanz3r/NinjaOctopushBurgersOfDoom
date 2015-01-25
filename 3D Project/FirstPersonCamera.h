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
};

#endif