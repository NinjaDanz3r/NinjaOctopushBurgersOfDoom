#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__

#include "Listener.h"

#include <AL/alc.h>

class SoundSystem {
	public:
		// Constructor
		SoundSystem();

		// Destructor
		~SoundSystem();

		// Get listener.
		Listener* listener() const;

		// Get instance of SoundSystem.
		static SoundSystem* getInstance();

		// Check for OpenAL Soft errors.
		static void checkError(const char* message);

	private:
		static SoundSystem* instance;

		ALCdevice *device;
		ALCcontext *context;

		Listener* _listener;
};

#endif