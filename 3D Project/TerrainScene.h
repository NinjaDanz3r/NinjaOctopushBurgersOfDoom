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

/// %Scene used to test terrain (height maps).
class TerrainScene : public Scene {
	public:
		/// Constructor
		TerrainScene();

		/// Destructor
		/**
		* Free allocated resources.
		*/
		~TerrainScene();

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

		Texture* blendMap;
		Texture* grassTexture;
		Texture* cliffTexture;
		Texture* sandTexture;
		Texture* snowTexture;
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