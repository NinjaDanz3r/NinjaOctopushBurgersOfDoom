#ifndef __SCENE_H__
#define __SCENE_H__

// A scene in the game, eg. title screen or in-game.
class Scene {
	public:
		// Returned when the scene has ended. Defines what should be done next.
		struct SceneEnd {
			public:
				enum Command {
					QUIT = 0,
					NEW_SCENE
				};

				// What to do next.
				Command command;

				// Next scene to go to. (nullptr if we shouldn't go to any scene next.)
				Scene* nextScene;

				SceneEnd(Command command, Scene* nextScene = nullptr);

			private:
				SceneEnd();
		};

		// Destructor
		virtual ~Scene() { }

		// Updates the scene.
		virtual SceneEnd* update(double time) = 0;

		// Renders the scene.
		virtual void render(int width, int height) = 0;
};

#endif