#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Object.h"
#include "IntersectionTesting.h"

/// Interface for renderable 3D geometry.
/**
 * Can be rendered using the default shaders.
 */
class Geometry : public Object {
	public:
		/// A vertex point.
		struct Vertex {
			/// Position.
			glm::vec3 position;
			/// Normal.
			glm::vec3 normal;
			/// %Texture coordinate.
			glm::vec2 textureCoordinate;
		};
		/// Destructor
		virtual ~Geometry() { }

		/// Get all the vertices.
		/**
		 * @return Array of vertices
		 */
		virtual Vertex* vertices() const = 0;

		/// Get local space AABB for object
		/**
		* Create a local space AABB for geometry object
		*/
		void createAabb();

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

		//Localspace AABB for the geometry
		AABB aabb;
};

#endif