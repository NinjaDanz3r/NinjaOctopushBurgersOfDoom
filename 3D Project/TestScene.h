#ifndef __TESTSCENE_H__
#define __TESTSCENE_H__

#include "Scene.h"

// Test scene. Used to test things.
class TestScene : public Scene {
	public:
		// Constructor
		TestScene();

		// Destructor
		~TestScene();

		// Updates the scene.
		SceneEnd* update(double time);

		// Renders the scene.
		void render(int width, int height);

	private:
		float rotation = 0.f;
};

#endif