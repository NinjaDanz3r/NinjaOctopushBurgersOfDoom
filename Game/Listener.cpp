#include "Listener.h"

#include <AL/al.h>
#include "SoundSystem.h"

const glm::vec3& Listener::position() const {
	return _position;
}

void Listener::setPosition(const glm::vec3& position) {
	_position = position;
	alListener3f(AL_POSITION, _position.x, _position.y, _position.z);
	SoundSystem::checkError("Couldn't set listener position.");
}

const glm::vec3& Listener::forward() const {
	return _forward;
}

const glm::vec3& Listener::up() const {
	return _up;
}

void Listener::setOrientation(glm::vec3& forward, glm::vec3& up) {
	ALfloat listenerOri[] = { forward.x, forward.y, forward.z, up.x, up.y, up.z };
	alListenerfv(AL_ORIENTATION, listenerOri);
	SoundSystem::checkError("Couldn't set listener orientation.");
}