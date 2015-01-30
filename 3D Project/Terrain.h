#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "Geometry.h"
#include <glm/glm.hpp>

// Represents a terrain object.
class Terrain : public Geometry {
public:
	// Constructor
	Terrain(const char* filename);

	// Destructor
	~Terrain();

	// Gets all the triangle vertices.
	Vertex* vertices() const;

	// Gets the number of vertices.
	unsigned int vertexCount() const;

	// Gets all the vertex indices.
	unsigned int* indices() const;

	// Gets the number of indicies.
	unsigned int indexCount() const;

	// Gets the Y-position of the terrain at a given location.
	float getY(float x, float z) const;

private:
	void generateVertices();
	void generateIndices();
	void filter3x3();
	float sampleHeight(int x, int y) const;
	void calculateNormals();

	Vertex *vertexData = nullptr;
	unsigned int vertexNr = 0;

	unsigned int* indexData = nullptr;
	unsigned int indexNr = 0;

	float** heightMap;
	glm::vec3** normals;
	int width;
	int height;
};

#endif