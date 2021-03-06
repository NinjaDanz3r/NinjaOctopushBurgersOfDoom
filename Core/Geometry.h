#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Core.h"
#include "AABB.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

class Geometry;
/** @ingroup core
 * @{
 */

/// Interface for renderable 3D geometry.
/**
* Can be rendered using the default shaders.
*/
class Geometry {
	public:
		/// A vertex point.
		struct Vertex {
			/// Position.
			glm::vec3 position;
			/// %Texture coordinate.
			glm::vec2 textureCoordinate;
			/// Normal.
			glm::vec3 normal;
			/// Tangent vector.
			glm::vec3 tangent;
		};
		/// Destructor
		CORE_EXPORT virtual ~Geometry();

		/// Get all the vertices.
		/**
		 * @return Array of vertices
		 */
		virtual Vertex* vertices() const = 0;

		/// Get local space AABB for object
		/**
		* Create a local space AABB for geometry object
		*/
		CORE_EXPORT void createAabb();

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

		/// Localspace AABB for the geometry
		AABB aabb;

		//Rectangle rectangle
		//Rectangle2D rect;

		/// Get the vertex array.
		/**
		 * @return The vertex array
		 */
		CORE_EXPORT GLuint vertexArray() const;

	protected:
		/// Generate vertex and index buffers.
		CORE_EXPORT void generateBuffers();

		/// Generate vertex array.
		CORE_EXPORT void generateVertexArray();

	private:
		GLuint vertexBuffer;
		GLuint indexBuffer;
		GLuint _vertexArray;
};

/** @} */

#endif