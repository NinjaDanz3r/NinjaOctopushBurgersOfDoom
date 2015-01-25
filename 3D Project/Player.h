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

		// Get movement speed (units/second)
		float movementSpeed() const;

		// Set movement speed (units/second)
		void setMovementSpeed(float movementSpeed);

		// Update movement.
		void update(double time);

		// Player camera.
		Camera* camera() const;

	private:
		Camera* _camera;
		float _movementSpeed = 1.0f;
};

#endif