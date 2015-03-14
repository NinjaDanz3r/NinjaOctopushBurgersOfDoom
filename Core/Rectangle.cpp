#include "Rectangle.h"

Rectangle::Rectangle(const glm::vec2& origin, const glm::vec2& dimensions) {
	this->origin = origin;
	this->dimensions = dimensions;
}

Rectangle::Rectangle(Model object, glm::mat4 matrix)
{
	glm::vec2 minValues, maxValues;
	Geometry::Vertex* currVert = object.vertices();
	minValues = maxValues = origin = glm::vec2(0.f, 0.f);
	unsigned int numVerts = object.vertexCount();

	for (unsigned int i = 0; i < numVerts; i++) {
		currVert[i].position = glm::vec3(matrix*glm::vec4(currVert[i].position, 0.f));
	}

	for (unsigned int i = 0; i < numVerts; i++) {
		if (currVert[i].position.x > maxValues.x)
			maxValues.x = currVert[i].position.x;
		else if (currVert[i].position.x < minValues.x)
			minValues.x = currVert[i].position.x;
		if (currVert[i].position.z > maxValues.y)
			maxValues.y = currVert[i].position.z;
		else if (currVert[i].position.z < minValues.y)
			minValues.y = currVert[i].position.z;
	}

	// Set origin
	origin.x = (minValues.x + maxValues.x) / 2;
	origin.y = (minValues.y + maxValues.y) / 2;

	// Width
	dimensions.x = maxValues.x - minValues.x;
	dimensions.y = maxValues.y - minValues.y;

	
}