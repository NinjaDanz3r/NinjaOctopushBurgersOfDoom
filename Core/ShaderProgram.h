#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include "Core.h"
#include <gl/glew.h>
#include <initializer_list>

class Shader;

/** @ingroup core
 * @{
 */

/// A GLSL shader program.
class ShaderProgram {
	public:
		/// Link shader program from provided shaders.
		/**
		 * Link together shaders into a shader program that can be run on the GPU.
		 *
		 * Sample:
		 * \code{.cpp}
		 * Shader* vertexShader = new Shader("default_vertex.glsl", GL_VERTEX_SHADER);
		 * Shader* geometryShader = new Shader("default_geometry.glsl", GL_GEOMETRY_SHADER);
		 * Shader* fragmentShader = new Shader("default_fragment.glsl", GL_FRAGMENT_SHADER);
		 * ShaderProgram* shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });
		 * \endcode
		 *
		 * @param shaders List of shaders to link together.
		 */
		CORE_EXPORT ShaderProgram(std::initializer_list<const Shader*> shaders);

		/// Destructor
		CORE_EXPORT ~ShaderProgram();

		/// Use shader program.
		/**
		 * Installs the program object as part of the current rendering state.
		 * @see <a href="https://www.opengl.org/sdk/docs/man4/html/glUseProgram.xhtml">glUseProgram</a>
		 */
		CORE_EXPORT void use() const;

		/// Get attribute location.
		/**
		 * @param name The name of the attribute variable whose location is to be queried.
		 * @return The location of an attribute variable or -1 if the named attribute variable is not an active attribute in the specified program object or if name starts with the reserved prefix "gl_"
		 */
		CORE_EXPORT GLuint attributeLocation(const char* name) const;

		/// Get uniform location.
		/**
		 * @param name The name of the uniform variable whose location is to be queried.
		 * @return The location of a uniform variable or -1 if name does not correspond to an active uniform variable in program, if name starts with the reserved prefix "gl_", or if name is associated with an atomic counter or a named uniform block
		 */
		CORE_EXPORT GLuint uniformLocation(const char* name) const;

	private:
		GLuint shaderProgram;
};

/** @} */

#endif