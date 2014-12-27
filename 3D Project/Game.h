#ifndef __GAME_H__
#define __GAME_H__

#include "Scene.h"
#include <GLFW/glfw3.h>

// Game class to handle the active scene.
class Game {
	public:
		// Constructor.
		Game(GLFWwindow* window);

		// Destructor
		~Game();

		// Update method. Called as often as possible.
		void update();

	private:
		GLFWwindow* window;
		Scene* currentScene;

		double lastTime;
};

#endif