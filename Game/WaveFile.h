#ifndef __WAVEFILE_H__
#define __WAVEFILE_H__

#include "SoundFile.h"

/** @ingroup game
 * @{
 */

/// WAVE implementation of SoundFile.
/**
 * Loads .wave-files.
 */
class WaveFile : public SoundFile {
	public:
		/// Loads the specified wave-file.
		/**
		 * @param filename Filename (relative or absolute) to wave-file.
		 */
		WaveFile(const char* filename);

		/// Destructor
		~WaveFile();

		/// Get raw audio data.
		/**
		* @return Raw audio data
		*/
		const char* data() const;

		/// Get data size.
		/**
		* @return The length of the raw audio data.
		*/
		ALsizei size() const;

		/// Get AL format.
		/**
		* 32-bit sound is not supported in OpenAL.
		* @return One of AL_FORMAT_MONO8, AL_FORMAT_MONO16, AL_FORMAT_STEREO8 or AL_FORMAT_STEREO16
		*/
		ALenum format() const;

		/// Get sample rate.
		/**
		* @return The sound file's sample rate (Hz)
		*/
		ALsizei sampleRate() const;

	private:
		char* _data;
		unsigned long dataSize;
		unsigned long _sampleRate;
		ALenum _format;

		static inline ALenum toALFormat(short channels, short bitsPerSample);
};

/** @} */

#endif