#include "FirstPersonCamera.h"
#include <glm\gtc\matrix_inverse.hpp>

void FirstPersonCamera::move(const glm::vec3& offset) {
	glm::vec3 movement;
	movement += offset.x * right();
	movement += offset.y * up();
	movement += offset.z * forward();

	Camera::move(movement);
}

void FirstPersonCamera::rotate(float horizontalAngle, float verticalAngle, float tiltAngle) {
	horizontalAngle = fmodf(Camera::horizontalAngle() + horizontalAngle, 360.f);
	if (horizontalAngle < 0.f)
		horizontalAngle += 360.f;

	verticalAngle = Camera::verticalAngle() + verticalAngle;
	if (verticalAngle > 85.f)
		verticalAngle = 85.f;
	else if (verticalAngle < -85.f)
		verticalAngle = -85.f;

	tiltAngle = fmodf(Camera::tiltAngle() + tiltAngle, 360.f);
	if (tiltAngle < 0.f)
		tiltAngle += 360.f;

	Camera::setAngles(horizontalAngle, verticalAngle, tiltAngle);
}

glm::vec3 FirstPersonCamera::forward() const {
	glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0, 0, -1, 1);
	return glm::vec3(forward);
}
glm::vec3 FirstPersonCamera::right() const {
	glm::vec4 right = glm::inverse(orientation()) * glm::vec4(1, 0, 0, 1);
	return glm::vec3(right);
}
glm::vec3 FirstPersonCamera::up() const {
	glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0, 1, 0, 1);
	return glm::vec3(up);
}