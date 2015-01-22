#include "SoundSystem.h"
#include "util.h"

#include <AL/al.h>

SoundSystem::SoundSystem() {
	// Open default audio device.
	device = alcOpenDevice(nullptr);
	if (!device)
		util::log("Couldn't open default audio device.");

	// Create audio context.
	context = alcCreateContext(device, nullptr);
	if (!alcMakeContextCurrent(context))
		util::log("Couldn't create audio context.");
}

SoundSystem::~SoundSystem() {
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void SoundSystem::checkError(const char* message) {
	ALenum error = alGetError();
	if (error != AL_NO_ERROR) {
		util::log(message);
		if (error == AL_INVALID_NAME) util::log("Invalid name");
		if (error == AL_INVALID_ENUM) util::log("Invalid enum");
		if (error == AL_INVALID_VALUE) util::log("Invalid value");
		if (error == AL_INVALID_OPERATION) util::log("Invalid operation");
		if (error == AL_OUT_OF_MEMORY) util::log("Out of memory like!");
	}
}