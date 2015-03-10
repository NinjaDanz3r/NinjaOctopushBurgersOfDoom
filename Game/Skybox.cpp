#include "Skybox.h"

Skybox::Vertex Skybox::vertices[8] = { {-1.f, 1.f, 1.f}, {1.f, 1.f, 1.f}, {-1.f, -1.f, 1.f}, {1.f, -1.f, 1.f}, {-1.f, 1.f, -1.f}, {1.f, 1.f, -1.f}, {-1.f, -1.f, -1.f}, {1.f, -1.f, -1.f} };
unsigned int Skybox::indices[36] = { 0, 1, 3, 0, 3, 2, 2, 3, 7, 2, 7, 6, 4, 7, 5, 4, 6, 7, 4, 5, 1, 4, 1, 0, 1, 5, 7, 1, 7, 3, 0, 6, 4, 0, 2, 6 };

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

Skybox::Skybox(const CubeMapTexture* texture) {
	this->texture = texture;

	vertexShader = new Shader("skybox_vertex.glsl", GL_VERTEX_SHADER);
	fragmentShader = new Shader("skybox_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, fragmentShader });

	// Texture unit 0 is for base images.
	shaderProgram->use();
	glUniform1i(shaderProgram->uniformLocation("cubeMapTexture"), 0);

	bindData();
}

Skybox::~Skybox() {
	delete shaderProgram;
	delete vertexShader;
	delete fragmentShader;

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Skybox::render(int width, int height, const Camera* camera) {
	shaderProgram->use();

	// Since our Z is always 1.0, we need to set depth buffer to render at <= 1.0 instead of the default < 1.0.
	GLint oldDepthFunctionMode;
	glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFunctionMode);
	glDepthFunc(GL_LEQUAL);

	// Cube map texture.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->textureID());

	// Set uniforms.
	glUniformMatrix4fv(shaderProgram->uniformLocation("viewMatrix"), 1, GL_FALSE, &camera->orientation()[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &camera->projection(width, height)[0][0]);

	glBindVertexArray(vertexAttribute);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	// Render
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

	glDepthFunc(oldDepthFunctionMode);
}

void Skybox::bindData() {
	// Vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Skybox::Vertex), vertices, GL_STATIC_DRAW);

	// Define vertex data layout
	glGenVertexArrays(1, &vertexAttribute);
	glBindVertexArray(vertexAttribute);
	glEnableVertexAttribArray(0);

	GLuint vertexPos = shaderProgram->attributeLocation("vertex_position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(Skybox::Vertex), BUFFER_OFFSET(0));

	// Index buffer
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}