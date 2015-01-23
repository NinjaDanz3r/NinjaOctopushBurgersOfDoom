#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Geometry.h"

// Represents a square.
class Square : public Geometry {
	public:
		// Create triangle data.
		Square();

		// Destructor
		~Square();

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