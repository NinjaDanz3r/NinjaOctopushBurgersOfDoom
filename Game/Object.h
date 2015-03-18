#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <glm/glm.hpp>

/** @ingroup game
 * @{
 */

/// Generic class to represent an object in the game world.
class Object {
	public:
		/// Destructor
		virtual ~Object() { }

		/// Get position.
		/**
		 * @return Position in the game world as a float-vector
		 */
		const glm::vec3& position() const;

		/// Set position.
		/**
		 * @param position Position in the game world as a float-vector.
		 */
		void setPosition(const glm::vec3& position);

		/// Set position.
		/**
		 * @param x X-position.
		 * @param y Y-position.
		 * @param z Z-position.
		 */
		void setPosition(float x, float y, float z);

		/// Get scale.
		/**
		 * Default: (1.0, 1.0, 1.0)
		 * @return Scale as a float-vector
		 */
		const glm::vec3& scale() const;

		/// Set scale.
		/**
		 * @param scale Scale as a float-vector.
		 */
		void setScale(const glm::vec3& scale);

		/// Set scale.
		/**
		 * @param xScale Scale along the X-axis.
		 * @param yScale Scale along the Y-axis.
		 * @param zScale Scale along the Z-axis.
		 */
		void setScale(float xScale, float yScale, float zScale);

		/// Move the current position by an offset.
		/**
		 * Move the object relative to its current position.
		 * @param offset Offset by which to move by.
		 */
		virtual void move(const glm::vec3& offset);

		/// Get horizontal angle.
		/**
		 * @return The object's horizontal rotation (in degrees).
		 */
		float horizontalAngle() const;

		/// Get vertical angle.
		/**
		 * @return The object's vertical rotation (in degrees).
		 */
		float verticalAngle() const;

		/// Get tilt angle.
		/**
		 * @return The object's tilt rotation (in degrees).
		 */
		float tiltAngle() const;

		/// Set rotation.
		/**
		 * @param horizontalAngle Horizontal rotation (in degrees).
		 * @param verticalAngle Vertical rotation (in degrees).
		 * @param tiltAngle Tilt rotation (in degrees).
		 */
		void setRotation(float horizontalAngle, float verticalAngle, float tiltAngle);

		/// Set rotation by an offset.
		/**
		 * Rotate the object relative to its current rotation.
		 * @param horizontalAngle Relative horizontal rotation (in degrees).
		 * @param verticalAngle Relative vertical rotation (in degrees).
		 * @param tiltAngle Relative tilt rotation (in degrees).
		 */
		virtual void rotate(float horizontalAngle, float verticalAngle, float tiltAngle);

		/// Get orientation matrix.
		/**
		 * @return Object's orientation matrix based on its rotation.
		 */
		glm::mat4 orientation() const;

		/// Get model matrix.
		/**
		 * @return The object's model matrix, containing translation, scaling and rotation.
		 */
		glm::mat4 modelMatrix() const;

	private:
		glm::vec3 _position = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 _scale = glm::vec3(1.f, 1.f, 1.f);

		float _horizontalAngle = 0.f;
		float _verticalAngle = 0.f;
		float _tiltAngle = 0.f;
};

/** @} */

#endif