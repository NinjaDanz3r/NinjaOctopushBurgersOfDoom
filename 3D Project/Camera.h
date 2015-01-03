#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>

// A camera in a 3D scene.
class Camera {
	public:
		// Destructor
		virtual ~Camera() { }

		// Get position.
		const glm::vec3& position() const;

		// Set position.
		void setPosition(const glm::vec3& position);

		// Move the current position by an offset.
		virtual void move(const glm::vec3& offset);

		// Get horizontal angle (in degrees).
		float horizontalAngle() const;

		// Get vertical angle (in degrees).
		float verticalAngle() const;

		// Get tilt angle (in degrees).
		float tiltAngle() const;

		// Set angles (in degrees).
		void setAngles(float horizontalAngle, float verticalAngle, float tiltAngle);

		// Set angles by an offset (in degrees).
		virtual void rotate(float horizontalAngle, float verticalAngle, float tiltAngle);

		// Orientation matrix.
		glm::mat4 orientation() const;

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
		glm::vec3 _position = glm::vec3(0.f, 0.f, 0.f);

		float _horizontalAngle = 0.f;
		float _verticalAngle = 0.f;
		float _tiltAngle = 0.f;

		float _fieldOfView = 45.f;
		float zNear = 0.5f;
		float zFar = 20.f;
};

#endif