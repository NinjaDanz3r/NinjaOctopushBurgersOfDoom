#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram(std::initializer_list<const Shader*> shaders) {
	shaderProgram = glCreateProgram();

	for (auto shader : shaders)
		glAttachShader(shaderProgram, shader->shaderID());

	glLinkProgram(shaderProgram);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(shaderProgram);
}

void ShaderProgram::use() const {
	glUseProgram(shaderProgram);
}

GLuint ShaderProgram::attributeLocation(const char* name) const {
	return glGetAttribLocation(shaderProgram, name);
}

GLuint ShaderProgram::uniformLocation(const char* name) const {
	return glGetUniformLocation(shaderProgram, name);
}