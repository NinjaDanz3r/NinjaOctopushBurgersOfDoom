#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Core.h"
#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include "ShaderProgram.h"

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
			/// Normal.
			glm::vec3 normal;
			/// %Texture coordinate.
			glm::vec2 textureCoordinate;
		};

		/// Destructor
		CORE_EXPORT virtual ~Geometry();

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

		/// Get the vertex buffer.
		/**
		 * @return The vertex buffer
		 */
		CORE_EXPORT GLuint vertexBuffer() const;

		/// Get the index buffer.
		/**
		 * @return The index buffer
		 */
		CORE_EXPORT GLuint indexBuffer() const;

		/// Generate vertex array object.
		/**
		 * Create a vertex array object describing the standard Geometry::Vertex.
		 * Shader program's vertex shader must take: vertex_position, vertex_normal and vertex_texture.
		 * @param shaderProgram The ShaderProgram to create the vertex array object for.
		 * @return Identifier for generated vertex array object
		 */
		CORE_EXPORT static GLuint generateVertexAttribute(ShaderProgram* shaderProgram);

	protected:
		/// Generate vertex and index buffers.
		CORE_EXPORT void generateBuffers();

	private:
		GLuint _vertexBuffer;
		GLuint _indexBuffer;
};

/** @} */

#endif