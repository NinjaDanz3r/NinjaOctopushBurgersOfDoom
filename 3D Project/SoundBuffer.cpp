#include "SoundBuffer.h"
#include "util.h"

SoundBuffer::SoundBuffer(SoundFile* soundFile) {
	// Create audio buffer.
	ALenum error;
	alGetError();
	alGenBuffers((ALuint)1, &_buffer);
	error = alGetError();
	if (error != AL_NO_ERROR)
		util::log("Couldn't create buffers.");

	// Set the buffer data.
	alBufferData(_buffer, soundFile->format(), soundFile->data(), soundFile->size(), soundFile->sampleRate());
	error = alGetError();
	if (error != AL_NO_ERROR) {
		util::log("Couldn't set buffer data.");
		if (error == AL_INVALID_NAME) util::log("Invalid name");
		if (error == AL_INVALID_ENUM) util::log("Invalid enum");
		if (error == AL_INVALID_VALUE) util::log("Invalid value");
		if (error == AL_INVALID_OPERATION) util::log("Invalid operation");
		if (error == AL_OUT_OF_MEMORY) util::log("Out of memory like!");
	}
}

SoundBuffer::~SoundBuffer() {
	alDeleteBuffers(1, &_buffer);
}

ALuint SoundBuffer::buffer() const {
	return _buffer;
}