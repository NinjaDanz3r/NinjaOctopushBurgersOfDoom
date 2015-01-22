#include "SoundBuffer.h"
#include "SoundSystem.h"
#include "util.h"

SoundBuffer::SoundBuffer(SoundFile* soundFile) {
	// Create audio buffer.
	alGetError();
	alGenBuffers((ALuint)1, &_buffer);
	SoundSystem::checkError("Couldn't create buffers.");

	// Set the buffer data.
	alBufferData(_buffer, soundFile->format(), soundFile->data(), soundFile->size(), soundFile->sampleRate());
	SoundSystem::checkError("Couldn't set buffer data.");
}

SoundBuffer::~SoundBuffer() {
	alDeleteBuffers(1, &_buffer);
}

ALuint SoundBuffer::buffer() const {
	return _buffer;
}