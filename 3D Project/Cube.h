<<<<<<< HEAD
#ifndef _CUBE_H_
#define _CUBE_H_
#include "Object.h"
class Cube :public Object
{
	public:
		// Represents a vertex point in a triangle.
		struct TriangleVertex
		{
			// Position.
			float x, y, z;
			// Texture coordinates.
			float u, v;
		};

		// Create triangle data.
		Cube();

		// Destructor
		~Cube();

		// Gets all the triangle vertexes.
		TriangleVertex* vertexes() const;

		// Gets the number of vertexes.
		int count() const;
	private:
		TriangleVertex *data = nullptr;
		int dataNr = 0;
};
#endif

=======
#ifndef __CUBE_H__
#define __CUBE_H__

#include "Geometry.h"

/// A cube.
class Cube : public Geometry {
	public:
		/// Create new cube at origo.
		Cube();

		/// Destructor
		~Cube();

		/// Get all the vertices.
		/**
		* @return Array of vertices
		*/
		Vertex* vertices() const;

		/// Get the number of vertices.
		/**
		* @return The number of vertices
		*/
		unsigned int vertexCount() const;

		/// Get all the vertex indices.
		/**
		* @return Array of vertex indices
		*/
		unsigned int* indices() const;

		/// Get the number of indicies.
		/**
		* @return The number of vertex indices.
		*/
		unsigned int indexCount() const;

	private:
		Vertex *vertexData = nullptr;
		unsigned int vertexNr = 0;

		unsigned int* indexData = nullptr;
		unsigned int indexNr = 0;
};

#endif
>>>>>>> origin/master
