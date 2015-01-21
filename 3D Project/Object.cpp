#include "Object.h"
#include <glm\gtc\matrix_transform.hpp>

const glm::vec3& Object::position() const {
	return _position;
}

void Object::setPosition(const glm::vec3& position) {
	_position = position;
}

const glm::vec3& Object::scale() const {
	return _scale;
}

void Object::setScale(const glm::vec3& scale) {
	_scale = scale;
}

void Object::move(const glm::vec3& offset) {
	_position += offset;
}

float Object::horizontalAngle() const {
	return _horizontalAngle;
}

float Object::verticalAngle() const {
	return _verticalAngle;
}

float Object::tiltAngle() const {
	return _tiltAngle;
}

void Object::setRotation(float horizontalAngle, float verticalAngle, float tiltAngle) {
	_horizontalAngle = horizontalAngle;
	_verticalAngle = verticalAngle;
	_tiltAngle = tiltAngle;
}

void Object::rotate(float horizontalAngle, float verticalAngle, float tiltAngle) {
	_horizontalAngle = fmodf(_horizontalAngle + horizontalAngle, 360.f);
	if (_horizontalAngle < 0.f)
		_horizontalAngle += 360.f;

	_verticalAngle = fmodf(_verticalAngle + verticalAngle, 360.f);
	if (_verticalAngle < 0.f)
		_verticalAngle += 360.f;

	_tiltAngle = fmodf(_tiltAngle + tiltAngle, 360.f);
	if (_tiltAngle < 0.f)
		_tiltAngle += 360.f;
}

glm::mat4 Object::orientation() const {
	glm::mat4 orientation;
	orientation = glm::rotate(orientation, glm::radians(_tiltAngle), glm::vec3(0, 0, 1));
	orientation = glm::rotate(orientation, glm::radians(_verticalAngle), glm::vec3(1, 0, 0));
	orientation = glm::rotate(orientation, glm::radians(_horizontalAngle), glm::vec3(0, 1, 0));
	return orientation;
}