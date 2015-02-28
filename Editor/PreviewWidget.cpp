#include "PreviewWidget.h"

#include <Texture2D.h>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

const glm::vec2 PreviewWidget::vertices[6] = { { 1.f, 1.f }, { -1.f, 1.f }, { -1.f, -1.f }, { 1.f, 1.f }, { -1.f, -1.f }, { 1.f, -1.f } };

PreviewWidget::PreviewWidget(QWidget* parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {

}

PreviewWidget::~PreviewWidget() {
	delete shaderProgram;
	delete vertexShader;
	delete fragmentShader;

	glDeleteBuffers(1, &vertexBuffer);

	delete texture;
}

void PreviewWidget::initializeGL() {
	glewInit();
	glEnable(GL_DEPTH_TEST);

	vertexShader = new Shader("showTexture_vertex.glsl", GL_VERTEX_SHADER);
	fragmentShader = new Shader("showTexture_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, fragmentShader });

	shaderProgram->use();
	bindQuad();

	texture = new Texture2D("../Game/Resources/Textures/kaleido.tga");
}

void PreviewWidget::paintGL() {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

void PreviewWidget::resizeGL(int width, int height) {
	this->width = width;
	this->height = height;
}

void PreviewWidget::bindQuad() {
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