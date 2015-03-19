#include "Rectangle2D.h"
#include "Frustum.h"

Rectangle2D::Rectangle2D(const glm::vec2& origin, const glm::vec2& dimensions) {
	this->origin = origin;
	this->dimensions = dimensions;
}

bool Rectangle2D::collide(const Frustum& frustum) const {
	return frustum.collide(*this);
}

Rectangle2D::Rectangle2D(const Geometry & geometry, const glm::mat4& matrix) {
	glm::vec2 minValues, maxValues;
	glm::vec3* currVert = new glm::vec3[geometry.vertexCount()];

	for (unsigned int i = 0; i < geometry.vertexCount(); i++) {
		currVert[i] = glm::vec3(matrix*glm::vec4(geometry.vertices()[i].position, 1.f));
	}
	minValues = maxValues = glm::vec2(currVert[0].x, currVert[0].z);

	// Get minimum rectangle from vertices, same principle as for minimum AABB
	for (unsigned int i = 0; i < geometry.vertexCount(); i++) {
		if (currVert[i].x > maxValues.x)
			maxValues.x = currVert[i].x;
		else if (currVert[i].x < minValues.x)
			minValues.x = currVert[i].x;
		if (currVert[i].z > maxValues.y)
			maxValues.y = currVert[i].z;
		else if (currVert[i].z < minValues.y)
			minValues.y = currVert[i].z;
	}

	// Set origin
	origin.x = (minValues.x + maxValues.x) / 2.f;
	origin.y = (minValues.y + maxValues.y) / 2.f;

	// Dimensions
	dimensions.x = maxValues.x - minValues.x;
	dimensions.y = maxValues.y - minValues.y;
}

bool Rectangle2D::overlaps(const Rectangle2D & otherRect){
	float rect1MinX, rect1MinY,rect1MaxX, rect1MaxY;
	float rect2MinX, rect2MinY, rect2MaxX, rect2MaxY;

	float dimX, dimY;

	dimX = dimensions.x / 2;
	dimY = dimensions.y / 2;

	//Points we will use in order to create triangles
	rect1MaxX = origin.x + dimX;
	rect1MaxY = origin.y + dimY; //Upper right corner

	rect1MinX = origin.x - dimX;
	rect1MinY = origin.y - dimY; //Lower left corner

	dimX = otherRect.dimensions.x / 2;
	dimY = otherRect.dimensions.y / 2;

	//Points we are going to test
	rect2MaxX = otherRect.origin.x + dimX;
	rect2MaxY = otherRect.origin.y + dimY; //Upper left corner

	rect2MinX = otherRect.origin.x - dimX;
	rect2MinY = otherRect.origin.y - dimY; //Lower right corner

	//If both are true, there is no overlap
	return  (!(rect1MinY > rect2MaxY || rect1MaxY < rect2MinY) && !(rect1MinX > rect2MaxX || rect1MaxX < rect2MinX));
}
