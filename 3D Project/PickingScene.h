#ifndef __PICKINGSCENE_H__
#define __PICKINGSCENE_H__

#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Geometry.h"
#include "Player.h"

/// %Scene used to test basic rendering technology.
class PickingScene : public Scene {
public:
	/// Constructor
	PickingScene();

	/// Destructor
	/**
	* Free allocated resources.
	*/
	~PickingScene();

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
	void bindTriangleData();

	// Shaders
	Shader* vertexShader;
	Shader* geometryShader;
	Shader* fragmentShader;
	ShaderProgram* shaderProgram;

	Texture* texture;
	Geometry* geometry;
	Player* player;

	// Vertex buffer.
	GLuint vertexBuffer = 0;
	GLuint vertexAttribute = 0;
	unsigned int vertexCount = 0;

	// Index buffer.
	GLuint indexBuffer = 0;
	unsigned int indexCount = 0;
};

#endif