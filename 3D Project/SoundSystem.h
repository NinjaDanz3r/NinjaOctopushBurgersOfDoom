#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__

#include <AL/alc.h>

class SoundSystem {
	public:
		// Constructor
		SoundSystem();

		// Destructor
		~SoundSystem();

		// Check for OpenAL Soft errors.
		static void checkError(const char* message);

	private:
		ALCdevice *device;
		ALCcontext *context;
};

#endif