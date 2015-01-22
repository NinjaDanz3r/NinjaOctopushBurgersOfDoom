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
};

#endif