#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Camera.h"

// The player character.
class Player {
	public:
		// Constructor
		Player();

		// Destructor
		~Player();

		// Update movement.
		void update(double time);

		// Player camera.
		Camera* camera() const;

	private:
		Camera* _camera;
};

#endif