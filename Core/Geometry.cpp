#include "Geometry.h"

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

Geometry::~Geometry() {
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Geometry::createAabb() {
	glm::vec3 minValues, maxValues, origin, dim;
	Vertex* currVert = vertices();
	minValues = maxValues = origin = glm::vec3(0.f, 0.f, 0.f);
	unsigned int numVerts = vertexCount();

	// Find minimum bounding points
	for (unsigned int i = 0; i < numVerts; i++) {
		if (currVert[i].position.x > maxValues.x)
			maxValues.x = currVert[i].position.x;
		else if (currVert[i].position.x < minValues.x)
			minValues.x = currVert[i].position.x;

		if (currVert[i].position.y > maxValues.y)
			maxValues.y = currVert[i].position.y;
		else if (currVert[i].position.y < minValues.y)
			minValues.y = currVert[i].position.y;

		if (currVert[i].position.z > maxValues.z)
			maxValues.z = currVert[i].position.z;
		else if (currVert[i].position.z < minValues.z)
			minValues.z = currVert[i].position.z;
	}

	// Set origin
	origin.x = (minValues.x + maxValues.x) / 2;
	origin.y = (minValues.y + maxValues.y) / 2;
	origin.z = (minValues.z + maxValues.z) / 2;

	// Width
	dim.x = maxValues.x - minValues.x;
	dim.y = maxValues.y - minValues.y;
	dim.z = maxValues.z - minValues.z;
	aabb = AABB(dim, origin, minValues, maxValues);
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