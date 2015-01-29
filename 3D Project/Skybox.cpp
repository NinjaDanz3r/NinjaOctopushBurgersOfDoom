#include "Skybox.h"

Skybox::Vertex Skybox::vertices[8] = { {-1.f, 1.f, 1.f}, {1.f, 1.f, 1.f}, {-1.f, -1.f, 1.f}, {1.f, -1.f, 1.f}, {-1.f, 1.f, -1.f}, {1.f, 1.f, -1.f}, {-1.f, -1.f, -1.f}, {1.f, -1.f, -1.f} };
unsigned int Skybox::indices[36] = { 0, 1, 3, 0, 3, 2, 2, 3, 7, 2, 7, 6, 4, 7, 5, 4, 6, 7, 4, 5, 1, 4, 1, 0, 1, 5, 7, 1, 7, 3, 0, 6, 4, 0, 2, 6 };

Skybox::Skybox(const CubeMapTexture* texture) {
	this->texture = texture;

	vertexShader = new Shader("skybox_vertex.glsl", GL_VERTEX_SHADER);
	fragmentShader = new Shader("skybox_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, fragmentShader });
}

Skybox::~Skybox() {
	delete shaderProgram;
	delete vertexShader;
	delete fragmentShader;
}

void Skybox::render(const Camera* camera) {
	
}