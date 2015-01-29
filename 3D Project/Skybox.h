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
		void render(const Camera* camera);

	private:
		static Vertex vertices[8];
		static unsigned int indices[36];

		const CubeMapTexture* texture;

		Shader* vertexShader;
		Shader* fragmentShader;
		ShaderProgram* shaderProgram;
};

#endif