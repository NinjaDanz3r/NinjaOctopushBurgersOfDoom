#ifndef __GAME_H__
#define __GAME_H__

#include <gl/glew.h>
#include <gl/GL.h>
#include <map>

#include "Scene.h"
#include "SoundSystem.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>

/// The game.
/** @defgroup game Game
 * @{
 */

/// Class to handle the active Scene.
/**
* Class to handle the active Scene and switch between scenes (eg. level scene or menu scene) during the course of the game.
*/
class Game {
	public:
		/// Constructor
		/**
		 * @param window Window for which to retrieve input, etc.
		 * @param sceneName Name of the scene to start on.
		 */
		Game(GLFWwindow* window, const char* sceneName);

		/// Destructor
		~Game();

		/// Update method. Called as often as possible.
		/**
		 * Updates input and the active scene as well as rendering the active scene and show FPS count (if this has been enabled in settings).
		 */
		void update();

	private:
		void setWindowTitle();
		void setSceneMap();
		void setScene(const char*);
		void assignKeyboardBindings();

		GLFWwindow* window;
		SoundSystem* soundSystem;
		Scene* currentScene;
		double lastTime;
		double prevFPSTime = 0.0;
		int frames = 0;
};

/** @} */

#endif