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

		// Move the current position by an offset.
		virtual void move(const glm::vec3& offset);

	private:
		glm::vec3 _position = glm::vec3(0.f, 0.f, 0.f);
};

#endif