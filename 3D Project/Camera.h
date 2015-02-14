#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Object.h"
#include <glm/glm.hpp>

/// A camera through which the world can be rendered.
class Camera : public Object {
	public:
		/// Create new camera.
		Camera();

		/// Destructor
		virtual ~Camera() { }

		/// Get the direction in which the camera is currently facing.
		/**
		 * @return The direction in which the camera is currently facing
		 */
		glm::vec3 forward() const;

		/// Get the direction to the right of the camera.
		/**
		 * @return The direction to the right of the camera
		 */
		glm::vec3 right() const;

		/// Get the camera's up-vector.
		/**
		 * @return The camera's up-vector
		 */
		glm::vec3 up() const;

		/// Get the camera's view matrix (translation and orientation).
		/**
		 * @return The view matrix
		 */
		glm::mat4 view() const;

		/// Get field of view.
		/**
		 * Default: 45.0
		 * @return Field of view (in degrees, 0.0-180.0)
		 */
		float fieldOfView() const;

		/// Set field of view.
		/**
		 * @param fieldOfView Field of view (in degrees, 0.0-180.0)
		 */
		void setFieldOfView(float fieldOfView);

		/// Get near plane.
		/**
		 * Default: 0.5
		 * @return Near plane
		 */
		float nearPlane() const;

		/// Get far plane.
		/**
		 * Default: 20.0
		 * @return Far plane
		 */
		float farPlane() const;

		/// Set near and far planes.
		/**
		 * @param near Near plane.
		 * @param far Far plane.
		 */
		void setNearAndFarPlanes(float near, float far);

		/// Get the projection matrix.
		/**
		 * @param width Width of context to render to.
		 * @param height Height of context to render to.
		 * @return Projection matrix
		 */
		glm::mat4 projection(int width, int height) const;

	private:
		float _fieldOfView = 45.f;
		float zNear = 0.5f;
		float zFar = 100.f;
};

#endif