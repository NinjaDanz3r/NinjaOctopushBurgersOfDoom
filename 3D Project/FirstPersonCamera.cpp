#include "FirstPersonCamera.h"

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

	Camera::setRotation(horizontalAngle, verticalAngle, tiltAngle);
}