#ifndef __FIRSTPERSONCAMERA_H__
#define __FIRSTPERSONCAMERA_H__

#include "Camera.h"

/// First person camera.
/**
 * Moves relative to the forward direction and vertical angle is limited to 85 degrees.
 */
class FirstPersonCamera : public Camera {
	public:
		/// Move the current position by an offset.
		/**
		 * Move the object relative to its current position, relative to the looking direction.
		 * Negative Z is relative to forward(), positive X relative to right() and positive Y relative to up().
		 * Eg. moving by (0.0, 0.0, -1.0) will move the camera one unit in the direction it is facing.
		 * @param offset Offset by which to move by.
		 */
		virtual void move(const glm::vec3& offset);

		/// Set angles by an offset.
		/**
		 * Rotate the object relative to its current rotation. Vertical angle limited to 85 degrees.
		 * @param horizontalAngle Relative horizontal rotation (in degrees).
		 * @param verticalAngle Relative vertical rotation (in degrees).
		 * @param tiltAngle Relative tilt rotation (in degrees).
		 */
		virtual void rotate(float horizontalAngle, float verticalAngle, float tiltAngle);
};

#endif