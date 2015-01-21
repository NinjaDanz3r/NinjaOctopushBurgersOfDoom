#include "Camera.h"
#include "settings.h"
#include <glm\gtc\matrix_transform.hpp>

Camera::Camera() {
	_fieldOfView = settings::fieldOfView();
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