#include "Player.h"
#include "input.h"

Player::Player() {
	_camera = new Camera();
	_camera->setPosition(glm::vec3(0.f, 0.f, 2.f));
	input::centerCursor();
}

Player::~Player() {
	delete _camera;
}

void Player::update(double time) {
	if (input::pressed(input::FORWARD))
		_camera->rotate((float)time * 10.f, (float)time * 10.f);

	_camera->rotate((float)input::cursorCenterX() * 0.1f, (float)input::cursorCenterY() * 0.1f);

	input::centerCursor();
}

Camera* Player::camera() const {
	return _camera;
}