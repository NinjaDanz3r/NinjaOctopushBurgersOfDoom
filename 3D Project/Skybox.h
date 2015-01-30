#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "CubeMapTexture.h"
#include "Camera.h"
#include "ShaderProgram.h"

class Skybox {
	public:
		struct Vertex {
			float x, y, z;
		};

		// Constructor
		Skybox(const CubeMapTexture* texture);

		// Destructor
		~Skybox();

		// Render skybox.
		void render(int width, int height, const Camera* camera);

	private:
		void bindData();

		static Vertex vertices[8];
		static unsigned int indices[36];

		const CubeMapTexture* texture;

		// Shaders
		Shader* vertexShader;
		Shader* fragmentShader;
		ShaderProgram* shaderProgram;

		// Vertex buffer
		GLuint vertexBuffer = 0;
		GLuint vertexAttribute = 0;

		// Index buffer.
		GLuint indexBuffer = 0;
};

#endif