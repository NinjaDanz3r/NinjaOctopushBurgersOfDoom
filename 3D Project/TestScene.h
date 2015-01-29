#ifndef __TESTSCENE_H__
#define __TESTSCENE_H__

#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Geometry.h"
#include "Player.h"

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