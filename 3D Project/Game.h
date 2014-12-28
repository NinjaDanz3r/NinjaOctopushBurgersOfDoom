#ifndef __GAME_H__
#define __GAME_H__

#include <gl/glew.h>
#include <gl/GL.h>

#include "Scene.h"

#define GLFW_DLL
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
		void setWindowFPS();
		void assignKeyboardBindings();

		GLFWwindow* window;
		Scene* currentScene;

		double lastTime;
		double prevFPSTime = 0.0;
		int frames = 0;
};

#endif