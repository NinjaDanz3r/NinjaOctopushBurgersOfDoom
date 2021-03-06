#ifndef __SHADER_H__
#define __SHADER_H__

#include "Core.h"
#include <gl/glew.h>
#include <string>

/** @ingroup core
 * @{
 */

/// A GLSL shader.
/**
 * Compiles and handles a GLSL shader. Shaders should be linked together into a ShaderProgram.
 */
class Shader {
	public:
		/// Compile shader.
		/**
		 * @param filename Filename (relative or absolute) to shader source code.
		 * @param shaderType %Shader type. One of GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
		 */
		CORE_EXPORT Shader(const char* filename, GLenum shaderType);

		/// Destructor
		CORE_EXPORT ~Shader();

		/// Get shader ID.
		/**
		 * Used when linking a ShaderProgram.
		 * @return Shader identifier
		 */
		CORE_EXPORT GLuint shaderID() const;

		/// Get shader type.
		/**
		 * @return %Shader type. One of GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
		 */
		CORE_EXPORT GLenum shaderType() const;

	private:
		// Helper method to read a file to a std::string.
		static std::string readFile(const char *filePath);

		GLuint shader;
		GLenum _shaderType;
};

/** @} */

#endif