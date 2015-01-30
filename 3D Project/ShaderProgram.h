#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include "Shader.h"
#include <initializer_list>

class ShaderProgram {
	public:
		// Constructor
		ShaderProgram(std::initializer_list<const Shader*> shaders);

		// Destructor
		~ShaderProgram();

		// Get shader program.
		GLuint shaderProgram() const;

	private:
		GLuint _shaderProgram;
};

#endif