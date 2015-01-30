#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <glm/glm.hpp>

// Generic class to represent an object in the game world.
class Object {
	public:
		// Destructor
		virtual ~Object() { }

		// Get position.
		const glm::vec3& position() const;

		// Set position.
		void setPosition(const glm::vec3& position);

		// Set position.
		void setPosition(float x, float y, float z);

		// Get scale.
		const glm::vec3& scale() const;

		// Set scale.
		void setScale(const glm::vec3& scale);

		// Set scale.
		void setScale(float xScale, float yScale, float zScale);

		// Move the current position by an offset.
		virtual void move(const glm::vec3& offset);

		// Get horizontal angle (in degrees).
		float horizontalAngle() const;

		// Get vertical angle (in degrees).
		float verticalAngle() const;

		// Get tilt angle (in degrees).
		float tiltAngle() const;

		// Set angles (in degrees).
		void setRotation(float horizontalAngle, float verticalAngle, float tiltAngle);

		// Set angles by an offset (in degrees).
		virtual void rotate(float horizontalAngle, float verticalAngle, float tiltAngle);

		// Orientation matrix.
		glm::mat4 orientation() const;

		// Model matrix.
		glm::mat4 modelMatrix() const;

	private:
		glm::vec3 _position = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 _scale = glm::vec3(1.f, 1.f, 1.f);

		float _horizontalAngle = 0.f;
		float _verticalAngle = 0.f;
		float _tiltAngle = 0.f;
};

#endif