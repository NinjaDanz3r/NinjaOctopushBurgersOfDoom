#ifndef __SCENE_H__
#define __SCENE_H__

/** @ingroup game
 * @{
 */

/// Interface for scenes in the game, eg. title screen or in-game.
class Scene {
	public:
		/// Returned when the scene has ended. Defines what should be done next.
		/**
		* Sample usage:
		* \code{.cpp}
		* SceneEnd* ExampleScene::update(double time) {
		*     if (input::triggered(input::FORWARD))
		*         return new SceneEnd(SceneEnd::NEW_SCENE, new TitleScene());
		*     return nullptr;
		* }
		* \endcode
		*/
		struct SceneEnd {
			public:
				/// Available commands.
				enum Command {
					/// Quit the game.
					QUIT = 0,
					/// Go to a new scene.
					NEW_SCENE
				};

				/// What to do next.
				Command command;

				/// Next scene to go to. (nullptr if we shouldn't go to any scene next.)
				Scene* nextScene;

				/// Create a new SceneEnd and define what should be done next.
				/**
				 * @param command What to do.
				 * @param nextScene New Scene to go to if command is NEW_SCENE.
				 */
				SceneEnd(Command command, Scene* nextScene = nullptr);

			private:
				SceneEnd();
		};

		/// Destructor
		virtual ~Scene() { }

		/// Update the scene.
		/**
		 * @param time Time since last frame (in seconds).
		 * @return SceneEnd-struct defining what to do next. nullptr if nothing should be done
		 */
		virtual SceneEnd* update(double time) = 0;

		/// Render the scene.
		/**
		 * @param width Width of the context.
		 * @param height Height of the context.
		 */
		virtual void render(int width, int height) = 0;
};

/** @} */

#endif