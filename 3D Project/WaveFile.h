#ifndef __WAVEFILE_H__
#define __WAVEFILE_H__

#include "SoundFile.h"

class WaveFile : public SoundFile {
	public:
		// Constructor
		WaveFile(const char* filename);

		// Destructor
		~WaveFile();

		// Get raw audio data.
		const char* data() const;

		// Get data size.
		ALsizei size() const;

		// Get AL format.
		ALenum format() const;

		// Get sample rate.
		ALsizei sampleRate() const;

	private:
		char* _data;
		unsigned long dataSize;
		unsigned long _sampleRate;
		ALenum _format;

		static inline ALenum toALFormat(short channels, short bitsPerSample);
};

#endif