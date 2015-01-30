#ifndef __CUBE_H__
#define __CUBE_H__

#include "Geometry.h"

// Represents a cube.
class Cube : public Geometry {
	public:
		// Create triangle data.
		Cube();

		// Destructor
		~Cube();

		// Gets all the triangle vertices.
		Vertex* vertices() const;

		// Gets the number of vertices.
		unsigned int vertexCount() const;

		// Gets all the vertex indices.
		unsigned int* indices() const;

		// Gets the number of indicies.
		unsigned int indexCount() const;

	private:
		Vertex *vertexData = nullptr;
		unsigned int vertexNr = 0;

		unsigned int* indexData = nullptr;
		unsigned int indexNr = 0;
};

#endif