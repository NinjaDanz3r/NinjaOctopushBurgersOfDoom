#include "Geometry.h"

void Geometry::createAabb()
{
	glm::vec3 minValues, maxValues;
	Vertex* currVert = Geometry::vertices();
	minValues = maxValues = glm::vec3(0.f, 0.f, 0.f);
	unsigned int numVerts = Geometry::vertexCount();
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
}