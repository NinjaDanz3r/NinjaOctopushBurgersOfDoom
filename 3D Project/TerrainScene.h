#ifndef __TERRAINSCENE_H__
#define __TERRAINSCENE_H__

#include "Scene.h"
#include "Shaders.h"
#include "Texture.h"
#include "Geometry.h"
#include "Player.h"

// Scene used to test terrain stuff (height maps).
class TerrainScene : public Scene {
	public:
		// Constructor
		TerrainScene();

		// Destructor
		~TerrainScene();

		// Updates the scene.
		SceneEnd* update(double time);

		// Renders the scene.
		void render(int width, int height);

	private:
		void bindTriangleData();

		Shaders* shaders;
		Texture* texture;
		Geometry* geometry;
		Player* player;

		// Vertex buffer.
		GLuint vertexBuffer = 0;
		GLuint vertexAttribute = 0;
		unsigned short vertexCount = 0;

		// Index buffer.
		GLuint indexBuffer = 0;
		unsigned int indexCount = 0;
};

#endif