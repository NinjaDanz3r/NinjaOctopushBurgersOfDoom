#ifndef __SOUNDFILE_H__
#define __SOUNDFILE_H__

#include <AL/al.h>

// Interface for sound files of various formats.
class SoundFile {
	public:
		// Destructor
		virtual ~SoundFile() { }

		// Get raw audio data.
		virtual const char* data() const = 0;

		// Get data size.
		virtual ALsizei size() const = 0;

		// Get AL format.
		virtual ALenum format() const = 0;

		// Get sample rate.
		virtual ALsizei sampleRate() const = 0;
};

#endif