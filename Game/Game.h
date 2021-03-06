#ifndef __GAME_H__
#define __GAME_H__

#include <gl/glew.h>
#include <map>
#include <vector>

struct GLFWwindow;
class SoundSystem;
class Scene;

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

		/// Additional data to display in window title.
		static char additionalData[128];

	private:
		void setWindowTitle();
		void setSceneMap();
		void setScene(const char*);

		void assignKeyboardBindings();

		GLFWwindow* window;
		SoundSystem* soundSystem;
		Scene* currentScene;
		std::vector<Scene*(*)()> sceneVector;
		double lastTime;
		double prevFPSTime = 0.0;
		int sceneNumber = 0;
		int frames = 0;
};

/** @} */

#endif