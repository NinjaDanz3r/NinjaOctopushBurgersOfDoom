#ifndef __PARTICLESCENE_H__
#define __PARTICLESCENE_H__

#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include <Geometry.h>
#include "Player.h"
#include "ParticleSystem.h"

/// %Scene used to test the ParticleSystem.
class ParticleScene : public Scene {
public:
	/// Constructor
	ParticleScene();

	/// Destructor
	/**
	* Free allocated resources.
	*/
	~ParticleScene();

	/// Update the scene.
	/**
	* @param time Time since last frame (in seconds).
	* @return SceneEnd-struct defining what to do next. nullptr if nothing should be done
	*/
	SceneEnd* update(double time);

	/// Render the scene.
	/**
	* @param width Width of the context.
	* @param height Height of the context.
	*/
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