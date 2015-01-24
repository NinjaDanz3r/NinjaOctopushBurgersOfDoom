#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "Geometry.h"

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

private:
	void generateVertices();
	void generateIndices();

	Vertex *vertexData = nullptr;
	unsigned int vertexNr = 0;

	unsigned int* indexData = nullptr;
	unsigned int indexNr = 0;

	float** heightMap;
	int width;
	int height;
};

#endif