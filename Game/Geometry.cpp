#include "Geometry.h"

void Geometry::createAabb()
{
	glm::vec3 minValues, maxValues, origin, dim;
	Vertex* currVert = vertices();
	minValues = maxValues = origin = glm::vec3(0.f, 0.f, 0.f);
	unsigned int numVerts = vertexCount();
	//Find minimum bounding points
	for (int i = 0; i < numVerts; i++)
	{
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
	//Set origin
	origin.x = (minValues.x + maxValues.x) / 2;
	origin.y = (minValues.y + maxValues.y) / 2;
	origin.z = (minValues.z + maxValues.z) / 2;
	//Width
	dim.x = maxValues.x - minValues.x;
	dim.y = maxValues.y - minValues.y;
	dim.z = maxValues.z - minValues.z;
	aabb = AABB(dim, origin, minValues, maxValues);
}