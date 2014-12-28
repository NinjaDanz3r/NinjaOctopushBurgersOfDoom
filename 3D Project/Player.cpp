#include "Player.h"
#include "input.h"

Player::Player() {
	_camera = new Camera();
	_camera->setPosition(glm::vec3(0.f, 0.f, 2.f));
	_camera->setAngles(0.f, 0.f, 15.f);
	input::centerCursor();
}

Player::~Player() {
	delete _camera;
}

void Player::update(double time) {
	float dx = (float)time * (input::pressed(input::RIGHT) - input::pressed(input::LEFT));
	float dz = (float)time * (input::pressed(input::BACKWARD) - input::pressed(input::FORWARD));
	_camera->move(glm::vec3(dx, 0.f, dz));

	_camera->rotate((float)input::cursorCenterX() * 0.1f, (float)input::cursorCenterY() * 0.1f, 0.f);

	input::centerCursor();
}

Camera* Player::camera() const {
	return _camera;
}