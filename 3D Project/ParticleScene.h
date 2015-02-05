#ifndef __TESTSCENE_H__
#define __TESTSCENE_H__

#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Geometry.h"
#include "Player.h"
#include "ParticleSystem.h"

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
	void bindPointData();

	//Shaders
	Shader* fragmentShader;
	Shader* geometryShader;
	Shader* vertexShader;
	ShaderProgram* shaderProgram;
	Texture* texture;

	Player* player;
	//Particle* particle;
	ParticleSystem* particleSystem;
	// Vertex buffer.
	GLuint vertexBuffer = 0;
	GLuint vertexAttribute = 0;
	unsigned int vertexCount = 0;

	// Index buffer.
	GLuint indexBuffer = 0;
	unsigned int indexCount = 0;
};

#endif