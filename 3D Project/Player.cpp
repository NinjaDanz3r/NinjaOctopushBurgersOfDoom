#include "Player.h"

Player::Player() {
	_camera = new Camera();
	_camera->setPosition(glm::vec3(0.f, 0.f, 2.f));
}

Player::~Player() {
	delete _camera;
}

void Player::update(double time) {
	_camera->rotate((float)time * 10.f, (float)time * 10.f);
}

Camera* Player::camera() const {
	return _camera;
}