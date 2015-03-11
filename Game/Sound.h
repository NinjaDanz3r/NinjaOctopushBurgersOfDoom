#ifndef __SOUND_H__
#define __SOUND_H__

#include "SoundBuffer.h"
#include <glm/glm.hpp>

/** @ingroup game
 * @{
 */

/// A sound source in the game world.
/**
 * Represents a sound source in the game world. If its SoundBuffer is in mono, the sound will be 3D and played relative to the Listener position. If the SoundBuffer is in stereo it will not be 3D.
 */
class Sound {
	public:
		/// Create new sound source.
		/**
		 * @param buffer The SoundBuffer containing the sound.
		 */
		Sound(SoundBuffer* buffer);

		/// Destructor
		~Sound();

		/// Get position.
		/**
		 * Starting position: (0.0, 0.0, 0.0).
		 * @return The sound source's position in the game world
		 */
		const glm::vec3& position() const;

		/// Set position.
		/**
		 * @param position New position for the sound source.
		 */
		void setPosition(const glm::vec3& position);

		/// Get pitch.
		/**
		 * Default 1.0.
		 * @return The sound source's pitch
		 */
		ALfloat pitch() const;

		/// Set pitch.
		/**
		 * @param pitch The sound source's pitch.
		 */
		void setPitch(ALfloat pitch);

		/// Get gain.
		/**
		 * Default 1.0.
		 * @return The sound's gain.
		 */
		ALfloat gain() const;

		/// Set gain.
		/**
		 * @param gain The sound's gain.
		 */
		void setGain(ALfloat gain);

		/// Get whether sound should loop.
		/**
		 * @return Whether the sound should loop
		 */
		ALboolean looping() const;

		/// Set whether sound should loop.
		/**
		 * @param loop Whether the sound should loop.
		 */
		void setLooping(ALboolean loop);

		/// Play sound.
		void play();

		/// Pause sound.
		void pause();

		/// Stop sound.
		void stop();

		/// Get state.
		/**
		 * @return One of AL_INITIAL, AL_PLAYING, AL_PAUSED or AL_STOPPED.
		 */
		ALint state() const;

	private:
		SoundBuffer* buffer;
		ALuint source;

		glm::vec3 _position = glm::vec3(0.f, 0.f, 0.f);
		ALfloat _pitch = 1.f;
		ALfloat _gain = 1.f;
		ALboolean loop = AL_FALSE;
};

/** @} */

#endif