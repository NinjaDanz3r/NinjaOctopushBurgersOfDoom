#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__

#include <AL/al.h>

class SoundSystem {
	public:
		// Check for OpenAL Soft errors.
		static void checkError(const char* message);
};

#endif