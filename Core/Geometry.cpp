#include "Geometry.h"

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

Geometry::~Geometry() {
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_indexBuffer);
}

GLuint Geometry::vertexBuffer() const {
	return _vertexBuffer;
}

GLuint Geometry::indexBuffer() const {
	return _indexBuffer;
}

GLuint Geometry::generateVertexAttribute(ShaderProgram* shaderProgram) {
	// Define vertex data layout
	GLuint vertexAttribute;
	glGenVertexArrays(1, &vertexAttribute);
	glBindVertexArray(vertexAttribute);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	GLuint vertexPos = shaderProgram->attributeLocation("vertex_position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(0));

	GLuint vertexNormal = shaderProgram->attributeLocation("vertex_normal");
	glVertexAttribPointer(vertexNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float) * 3));

	GLuint vertexTexture = shaderProgram->attributeLocation("vertex_texture");
	glVertexAttribPointer(vertexTexture, 2, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float) * 6));

	return vertexAttribute;
}

void Geometry::generateBuffers() {
	// Vertex buffer
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount() * sizeof(Vertex), vertices(), GL_STATIC_DRAW);

	// Index buffer
	glGenBuffers(1, &_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount() * sizeof(unsigned int), indices(), GL_STATIC_DRAW);
}