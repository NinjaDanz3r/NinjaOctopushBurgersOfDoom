#include "Player.h"
#include "FirstPersonCamera.h"
#include "input.h"
#include "settings.h"

Player::Player() {
	_camera = new FirstPersonCamera();
	_camera->setPosition(glm::vec3(0.f, 0.f, 2.f));
	
	input::centerCursor();
	prevMX = static_cast<float>(input::cursorX());
	prevMY = static_cast<float>(input::cursorY());
}

Player::~Player() {
	delete _camera;
}

float Player::movementSpeed() const {
	return _movementSpeed;
}

void Player::setMovementSpeed(float movementSpeed) {
	_movementSpeed = movementSpeed;
}

void Player::update(double time) {
	float dx = (float)time * _movementSpeed * (input::pressed(input::RIGHT) - input::pressed(input::LEFT));
	float dz = (float)time * _movementSpeed * (input::pressed(input::FORWARD) - input::pressed(input::BACKWARD));
	_camera->move(glm::vec3(dx, 0.f, dz));

	float mdx = static_cast<float>(input::cursorX()) - prevMX;
	float mdy = static_cast<float>(input::cursorY()) - prevMY;
	_camera->rotate(mdx * 0.2f * settings::mouseSensitivity(), mdy * 0.2f * settings::mouseSensitivity(), 0.f);

	if (settings::centerMouseCursor())
		input::centerCursor();

	prevMX = input::cursorX();
	prevMY = input::cursorY();
}

Camera* Player::camera() const {
	return _camera;
}