#ifndef __TESTSCENE_H__
#define __TESTSCENE_H__

#include "Scene.h"
#include "Shaders.h"
#include "Texture.h"
#include "Geometry.h"
#include "Player.h"
#include "Particle.h"

// Test scene. Used to test things.
class ParticleScene : public Scene {
public:
	// Constructor
	ParticleScene();

	// Destructor
	~ParticleScene();

	// Updates the scene.
	SceneEnd* update(double time);

	// Renders the scene.
	void render(int width, int height);

private:
	void bindTriangleData();

	Shaders* shaders;
	Texture* texture;
	Player* player;
	Particle* particle;
	// Vertex buffer.
	GLuint vertexBuffer = 0;
	GLuint vertexAttribute = 0;
	unsigned int vertexCount = 0;

	// Index buffer.
	GLuint indexBuffer = 0;
	unsigned int indexCount = 0;
};

#endif