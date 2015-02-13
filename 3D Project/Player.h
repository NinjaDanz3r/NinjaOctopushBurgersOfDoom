#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Camera.h"

/// The player character.
/**
 * Holds a Camera object and manipulates that camera's position and rotation based on player input (first person camera).
 */
class Player {
	public:
		/// Creates a new player object.
		Player();

		/// Destructor
		~Player();

		/// Get movement speed.
		/**
		 * @return Movement speed (units/second)
		 */
		float movementSpeed() const;

		/// Set movement speed.
		/**
		 * @param movementSpeed Movement speed (units/second).
		 */
		void setMovementSpeed(float movementSpeed);

		/// Update movement.
		/**
		 * Updates position and orientation based on player input.
		 * @param time Time since last frame (in seconds).
		 */
		void update(double time);

		/// Get player camera.
		/**
		 * @return The player's Camera object
		 */
		Camera* camera() const;

	private:
		Camera* _camera;
		float _movementSpeed = 1.0f;
		float prevMX, prevMY;
};

#endif