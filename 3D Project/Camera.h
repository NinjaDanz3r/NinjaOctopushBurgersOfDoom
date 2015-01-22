#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Object.h"
#include <glm/glm.hpp>

// A camera in a 3D scene.
class Camera : public Object {
	public:
		// Constructor
		Camera();

		// Destructor
		virtual ~Camera() { }

		// The direction in which the camera is currently facing.
		glm::vec3 forward() const;

		// The direction representing the direction to the right of the camera.
		glm::vec3 right() const;

		// The camera's up-vector.
		glm::vec3 up() const;

		// The camera's view matrix (translation and orientation).
		glm::mat4 view() const;

		// Get field of view (in degrees, 0-180).
		float fieldOfView() const;

		// Set field of view (in degrees, 0-180).
		void setFieldOfView(float fieldOfView);

		// Get near plane.
		float nearPlane() const;

		// Get far plane.
		float farPlane() const;

		// Set near and far planes.
		void setNearAndFarPlanes(float near, float far);

		// Projection matrix.
		glm::mat4 projection(int width, int height) const;

	private:
		float _fieldOfView = 45.f;
		float zNear = 0.5f;
		float zFar = 20.f;
};

#endif