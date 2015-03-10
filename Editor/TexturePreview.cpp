#include "TexturePreview.h"

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

const glm::vec2 TexturePreview::vertices[6] = { { 1.f, 1.f }, { -1.f, 1.f }, { -1.f, -1.f }, { 1.f, 1.f }, { -1.f, -1.f }, { 1.f, -1.f } };

TexturePreview::TexturePreview() {
	vertexShader = new Shader("showTexture_vertex.glsl", GL_VERTEX_SHADER);
	fragmentShader = new Shader("showTexture_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, fragmentShader });

	shaderProgram->use();
	bindQuad();
}

TexturePreview::~TexturePreview() {
	delete shaderProgram;
	delete vertexShader;
	delete fragmentShader;

	glDeleteBuffers(1, &vertexBuffer);
}

void TexturePreview::setTexture(Texture* texture) {
	this->texture = texture;
}

void TexturePreview::render(int width, int height) const {
	if (texture != nullptr) {
		shaderProgram->use();

		// Texture unit 0 is for base images.
		glUniform1i(shaderProgram->uniformLocation("baseImage"), 0);

		glBindVertexArray(vertexAttribute);

		// Base image texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->textureID());

		glm::vec2 screenSize(width, height);
		glUniform2fv(shaderProgram->uniformLocation("screenSize"), 1, &screenSize[0]);

		// Draw the triangles
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void TexturePreview::bindQuad() {
	vertexCount = 6;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);

	// Define vertex data layout
	glGenVertexArrays(1, &vertexAttribute);
	glBindVertexArray(vertexAttribute);
	glEnableVertexAttribArray(0);

	GLuint vertexPos = shaderProgram->attributeLocation("vertex_position");
	glVertexAttribPointer(vertexPos, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), BUFFER_OFFSET(0));
}