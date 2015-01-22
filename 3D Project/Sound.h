#ifndef __SOUND_H__
#define __SOUND_H__

#include "SoundBuffer.h"
#include <glm/glm.hpp>

class Sound {
	public:
		// Constructor
		Sound(SoundBuffer* buffer);

		// Destructor
		~Sound();

		// Get position.
		const glm::vec3& position() const;

		// Set position.
		void setPosition(const glm::vec3& position);

		// Get pitch.
		ALfloat pitch() const;

		// Set pitch.
		void setPitch(ALfloat pitch);

		// Get gain.
		ALfloat gain() const;

		// Set gain.
		void setGain(ALfloat gain);

		// Get whether sound should loop.
		ALboolean looping() const;

		// Set whether sound should loop.
		void setLooping(ALboolean loop);

		// Play sound.
		void play();

		// Pause sound.
		void pause();

		// Stop sound.
		void stop();

		// Get state. (AL_INITIAL, AL_PLAYING, AL_PAUSED or AL_STOPPED)
		ALint state() const;

	private:
		SoundBuffer* buffer;
		ALuint source;

		glm::vec3 _position = glm::vec3(0.f, 0.f, 0.f);
		ALfloat _pitch = 1.f;
		ALfloat _gain = 1.f;
		ALboolean loop = AL_FALSE;
};

#endif