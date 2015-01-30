#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::initializer_list<const Shader*> shaders) {
	_shaderProgram = glCreateProgram();

	for (auto shader : shaders)
		glAttachShader(_shaderProgram, shader->shaderID());

	glLinkProgram(_shaderProgram);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(_shaderProgram);
}

GLuint ShaderProgram::shaderProgram() const {
	return _shaderProgram;
}