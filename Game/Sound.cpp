#include "Sound.h"

#include <AL/alc.h>
#include "SoundSystem.h"

Sound::Sound(SoundBuffer* buffer) {
	alGenSources((ALuint)1, &source);

	alSourcef(source, AL_PITCH, _pitch);
	alSourcef(source, AL_GAIN, _gain);
	alSource3f(source, AL_POSITION, _position.x, _position.y, _position.z);
	alSource3f(source, AL_VELOCITY, 0.f, 0.f, 0.f);
	alSourcei(source, AL_LOOPING, loop);

	alSourcei(source, AL_BUFFER, buffer->buffer());
	SoundSystem::checkError("Couldn't set sound source buffer.");
}

Sound::~Sound() {
	alDeleteSources(1, &source);
}

const glm::vec3& Sound::position() const {
	return _position;
}

void Sound::setPosition(const glm::vec3& position) {
	_position = position;
	alSource3f(source, AL_POSITION, _position.x, _position.y, _position.z);
}

ALfloat Sound::pitch() const {
	return _pitch;
}

void Sound::setPitch(ALfloat pitch) {
	_pitch = pitch;
	alSourcef(source, AL_PITCH, _pitch);
}

ALfloat Sound::gain() const {
	return _gain;
}

void Sound::setGain(ALfloat gain) {
	_gain = gain;
	alSourcef(source, AL_GAIN, _gain);
}

ALboolean Sound::looping() const {
	return loop;
}

void Sound::setLooping(ALboolean loop) {
	this->loop = loop;
	alSourcei(source, AL_LOOPING, loop);
}

void Sound::play() {
	alSourcePlay(source);
	SoundSystem::checkError("Couldn't play sound.");
}

void Sound::pause() {
	alSourcePause(source);
	SoundSystem::checkError("Couldn't pause sound.");
}

void Sound::stop() {
	alSourceStop(source);
	SoundSystem::checkError("Couldn't pause sound.");
}

ALint Sound::state() const {
	ALint _state;
	alGetSourcei(source, AL_SOURCE_STATE, &_state);
	return _state;
}