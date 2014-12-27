#ifndef __SCENE_H__
#define __SCENE_H__

// A scene in the game, eg. title screen or in-game.
class Scene {
	public:
		// Destructor
		virtual ~Scene() { }

		// Updates the scene.
		virtual void update(double time) = 0;

		// Renders the scene.
		virtual void render(int width, int height) = 0;
};

#endif