#ifndef __CUBE_H__
#define __CUBE_H__

#include <Geometry.h>

/** @ingroup game
 * @{
 */

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

/** @} */

#endif