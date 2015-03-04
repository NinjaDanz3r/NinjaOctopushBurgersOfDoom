#ifndef __SOUNDBUFFER_H__
#define __SOUNDBUFFER_H__

#include "SoundFile.h"
#include <AL\al.h>

/** @ingroup game
 * @{
 */

/// Wrapper for OpenAL buffers.
class SoundBuffer {
	public:
		/// Create a sound buffer from a sound file.
		/**
		 * @param soundFile The sound file containing the sound.
		 */
		SoundBuffer(SoundFile* soundFile);

		/// Destructor
		~SoundBuffer();

		/// Get AL buffer.
		/**
		 * @return The OpenAL buffer ID.
		 */
		ALuint buffer() const;

	private:
		ALuint _buffer;
};

/** @} */

#endif