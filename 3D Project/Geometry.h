#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Object.h"

// Interface for all forms of geometry, eg. BTHSquares or Models.
class Geometry : public Object {
	public:
		// Represents a vertex point in a triangle.
		struct Vertex
		{
			// Position.
			float x, y, z;
			// Texture coordinates.
			float u, v;
		};

		// Destructor
		virtual ~Geometry() { }

		// Gets all the triangle vertices.
		virtual Vertex* vertices() const = 0;

		// Gets the number of vertices.
		virtual unsigned int vertexCount() const = 0;

		// Gets all the vertex indices.
		virtual unsigned int* indices() const = 0;

		// Gets the number of indicies.
		virtual unsigned int indexCount() const = 0;
};

#endif