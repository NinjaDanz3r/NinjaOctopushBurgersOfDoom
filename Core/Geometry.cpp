#include "Geometry.h"

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

Geometry::~Geometry() {
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

GLuint Geometry::vertexArray() const {
	return _vertexArray;
}

void Geometry::generateBuffers() {
	// Vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount() * sizeof(Vertex), vertices(), GL_STATIC_DRAW);

	// Index buffer
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount() * sizeof(unsigned int), indices(), GL_STATIC_DRAW);
}

void Geometry::generateVertexArray() {
	// Define vertex data layout
	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float) * 6));

	glBindVertexArray(0);
}