#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Object.h"

/// Interface for renderable 3D geometry.
/**
 * Can be rendered using the default shaders.
 */
class Geometry : public Object {
	public:
		/// A vertex point.
		struct Vertex
		{
			/// X-position.
			float x;
			/// Y-position.
			float y;
			/// Z-position.
			float z;
			/// Normal x.
			float normalX;
			/// Normal y.
			float normalY;
			/// Normal z.
			float normalZ;
			/// Texture x-coordinate.
			float u;
			/// Texture y-coordinate.
			float v;
		};

		/// Destructor
		virtual ~Geometry() { }

		/// Get all the vertices.
		/**
		 * @return Array of vertices
		 */
		virtual Vertex* vertices() const = 0;

		/// Get the number of vertices.
		/**
		 * @return The number of vertices
		 */
		virtual unsigned int vertexCount() const = 0;

		/// Get all the vertex indices.
		/**
		 * @return Array of vertex indices
		 */
		virtual unsigned int* indices() const = 0;

		/// Get the number of indicies.
		/**
		 * @return The number of vertex indices.
		 */
		virtual unsigned int indexCount() const = 0;
};

#endif