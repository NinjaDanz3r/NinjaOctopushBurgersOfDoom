#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include "Shader.h"
#include <initializer_list>

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
		ShaderProgram(std::initializer_list<const Shader*> shaders);

		/// Destructor
		~ShaderProgram();

		/// Get shader program ID.
		/**
		 * Used when setting which shader program to render with or for getting uniform locations.
		 * @return %Shader program identifier
		 */
		GLuint shaderProgram() const;

	private:
		GLuint _shaderProgram;
};

#endif