#ifndef __SOUNDBUFFER_H__
#define __SOUNDBUFFER_H__

#include "SoundFile.h"
#include <AL\al.h>

class SoundBuffer {
	public:
		// Constructor
		SoundBuffer(SoundFile* soundFile);

		// Destructor
		~SoundBuffer();

		// Get AL buffer.
		ALuint buffer() const;

	private:
		ALuint _buffer;
};

#endif