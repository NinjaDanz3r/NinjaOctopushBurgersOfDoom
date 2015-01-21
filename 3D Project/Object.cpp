#include "Object.h"

const glm::vec3& Object::position() const {
	return _position;
}

void Object::setPosition(const glm::vec3& position) {
	_position = position;
}

void Object::move(const glm::vec3& offset) {
	_position += offset;
}