#include "Camera.h"
#include "settings.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\matrix_inverse.hpp>

Camera::Camera() {
	_fieldOfView = settings::fieldOfView();
}

glm::vec3 Camera::forward() const {
	glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0, 0, -1, 1);
	return glm::vec3(forward);
}
glm::vec3 Camera::right() const {
	glm::vec4 right = glm::inverse(orientation()) * glm::vec4(1, 0, 0, 1);
	return glm::vec3(right);
}
glm::vec3 Camera::up() const {
	glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0, 1, 0, 1);
	return glm::vec3(up);
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