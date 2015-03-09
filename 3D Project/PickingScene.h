#ifndef __PICKINGSCENE_H__
#define __PICKINGSCENE_H__

#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Geometry.h"
#include "Player.h"
#include <vector>

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
	Texture* diffuse;
	Texture* normal;
	Texture* specular;

	Texture* texture;
	std::vector<Geometry*> multiGeometry;
	int numModels = 50;
	//Geometry* geometry;
	Player* player;

	// Vertex buffer.
	//GLuint vertexBuffer = 0;
	//GLuint vertexAttribute = 0;
	GLuint* vertexBuffers;
	GLuint* vertexAttributes;

	GLuint hitData = 1;
	GLuint hitAttrib = 1;

	GLboolean isHit = false;
	unsigned int vertexCount = 0;

	// Index buffer.
	//GLuint indexBuffer = 0;
	GLuint* indexBuffers;
	unsigned int indexCount = 0;
};

#endif