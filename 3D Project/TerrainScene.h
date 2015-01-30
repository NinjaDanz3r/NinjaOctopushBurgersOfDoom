#ifndef __TERRAINSCENE_H__
#define __TERRAINSCENE_H__

#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "CubeMapTexture.h"
#include "Geometry.h"
#include "Player.h"
#include "Skybox.h"

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

		// Shaders
		Shader* vertexShader;
		Shader* geometryShader;
		Shader* fragmentShader;
		ShaderProgram* shaderProgram;

		Texture* texture;
		Geometry* geometry;
		Player* player;

		// Skybox
		Skybox* skybox;
		CubeMapTexture* skyboxTexture;

		// Vertex buffer.
		GLuint vertexBuffer = 0;
		GLuint vertexAttribute = 0;
		unsigned int vertexCount = 0;

		// Index buffer.
		GLuint indexBuffer = 0;
		unsigned int indexCount = 0;
};

#endif