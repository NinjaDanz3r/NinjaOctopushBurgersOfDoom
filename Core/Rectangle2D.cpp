#include "Rectangle2D.h"
#include "Frustum.h"

Rectangle2D::Rectangle2D(const glm::vec2& origin, const glm::vec2& dimensions) {
	this->origin = origin;
	this->dimensions = dimensions;
}

bool Rectangle2D::collide(const Frustum& frustum) const {
	return frustum.collide(*this);
}

Rectangle2D::Rectangle2D(const Geometry & geometry, glm::mat4 matrix)
{
	glm::vec2 minValues, maxValues;
	Geometry::Vertex* currVert = geometry.vertices();
	minValues = maxValues = origin = glm::vec2(0.f, 0.f);
	unsigned int numVerts = geometry.vertexCount();

	for (unsigned int i = 0; i < numVerts; i++) {
		currVert[i].position = glm::vec3(matrix*glm::vec4(currVert[i].position, 0.f));
	}

	//Get minimum rectangle from vertices, same principle as for minimum AABB
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


bool Rectangle2D::overlaps(const Rectangle2D & otherRect){
	glm::vec2 verts1[2];
	glm::vec2 verts2[2];

	float dimX, dimY;

	dimX = dimensions.x / 2;
	dimY = dimensions.y / 2;

	//Points we will use in order to create triangles
	verts1[0] = glm::vec2(origin.x + dimX, origin.y + dimY); //Upper right corner
	verts1[1] = glm::vec2(origin.x - dimX, origin.y - dimY); //Lower left corner

	dimX = otherRect.dimensions.x / 2;
	dimY = otherRect.dimensions.y / 2;

	//Points we are going to test
	verts2[0] = glm::vec2(otherRect.origin.x + dimX, otherRect.origin.y + dimY); //Upper right corner
	verts2[1] = glm::vec2(otherRect.origin.x - dimX, otherRect.origin.y - dimY); //Lower left corner

	//if all conditions are true, then there is no overlap since the rectangle 2 is entirely outside of rectangle 1
	return (
		(verts1[1].x < verts2[0].x) &&	//Rectangle 1 left to the left of rectangle 2 right edge
		(verts1[0].x > verts2[1].x) &&	//Rectangle 1 right to the left of rectangle 2 left edge
		(verts1[0].y < verts2[1].y) &&	//Rectangle 1 top above of rectangle 2 bottom edge
		(verts1[1].y > verts2[0].y)		//Rectangle 1 bottom below of rectangle 2 top edge
		);
}
