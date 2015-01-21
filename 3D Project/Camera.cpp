#include "Camera.h"
#include "settings.h"
#include <glm\gtc\matrix_transform.hpp>

Camera::Camera() {
	_fieldOfView = settings::fieldOfView();
}

float Camera::horizontalAngle() const {
	return _horizontalAngle;
}

float Camera::verticalAngle() const {
	return _verticalAngle;
}

float Camera::tiltAngle() const {
	return _tiltAngle;
}

void Camera::setAngles(float horizontalAngle, float verticalAngle, float tiltAngle) {
	_horizontalAngle = horizontalAngle;
	_verticalAngle = verticalAngle;
	_tiltAngle = tiltAngle;
}

void Camera::rotate(float horizontalAngle, float verticalAngle, float tiltAngle) {
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

glm::mat4 Camera::orientation() const {
	glm::mat4 orientation;
	orientation = glm::rotate(orientation, glm::radians(_tiltAngle), glm::vec3(0, 0, 1));
	orientation = glm::rotate(orientation, glm::radians(_verticalAngle), glm::vec3(1, 0, 0));
	orientation = glm::rotate(orientation, glm::radians(_horizontalAngle), glm::vec3(0, 1, 0));
	return orientation;
}

glm::mat4 Camera::view() const {
	return orientation() * glm::translate(glm::mat4(), -position());
}

float Camera::fieldOfView() const {
	return _fieldOfView;
}

void Camera::setFieldOfView(float fieldOfView) {
	_fieldOfView = fieldOfView;
}

float Camera::nearPlane() const {
	return zNear;
}

float Camera::farPlane() const {
	return zFar;
}

void Camera::setNearAndFarPlanes(float near, float far) {
	zNear = near;
	zFar = far;
}

glm::mat4 Camera::projection(int width, int height) const {
	return glm::perspective(glm::radians(_fieldOfView), static_cast<float>(width)/height, zNear, zFar);
}