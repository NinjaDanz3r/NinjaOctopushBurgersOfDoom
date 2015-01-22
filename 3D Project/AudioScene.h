#ifndef __AUDIOSCENE_H__
#define __AUDIOSCENE_H__

#include "Scene.h"
#include "Shaders.h"
#include "Texture.h"
#include "BTHSquare.h"
#include "Player.h"

// Test scene. Used to test things.
class AudioScene : public Scene {
public:
	// Constructor
	AudioScene();

	// Destructor
	~AudioScene();

	// Updates the scene.
	SceneEnd* update(double time);

	// Renders the scene.
	void render(int width, int height);

private:
	void bindTriangleData();

	Shaders* shaders;
	Texture* texture;
	BTHSquare* bthSquare;
	Player* player;

	// Vertex buffer.
	GLuint gVertexBuffer = 0;
	GLuint gVertexAttribute = 0;
	int vertexCount = 0;
};

#endif