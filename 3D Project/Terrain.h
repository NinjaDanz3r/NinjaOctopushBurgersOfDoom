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
	unsigned short vertexCount() const;

	// Gets all the vertex indices.
	unsigned short* indices() const;

	// Gets the number of indicies.
	unsigned int indexCount() const;

private:
	Vertex *vertexData = nullptr;
	int vertexNr = 0;

	unsigned short* indexData = nullptr;
	int indexNr = 0;

	int width;
	int height;
};

#endif