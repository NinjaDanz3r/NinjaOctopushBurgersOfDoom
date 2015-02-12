#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__

#include "Listener.h"

#include <AL/alc.h>

/// Handles OpenAL sound.
/**
 * There should only be one instance.
 */
class SoundSystem {
	public:
		/// Initializes OpenAL sound.
		/**
		 * Creates default audio device, audio context and Listener.
		 */
		SoundSystem();

		/// Destructor
		/**
		 * Closes the audio device and destroys the audio context.
		 */
		~SoundSystem();

		/// Get listener.
		/**
		 * @return The listener
		 */
		Listener* listener() const;

		/// Get instance of SoundSystem.
		/**
		 * @return The SoundSystem instance
		 */
		static SoundSystem* getInstance();

		/// Check for OpenAL errors.
		/**
		 * @param message Message to print to standard error if an error was encountered.
		 */
		static void checkError(const char* message);

	private:
		static SoundSystem* instance;

		ALCdevice *device;
		ALCcontext *context;

		Listener* _listener;
};

#endif