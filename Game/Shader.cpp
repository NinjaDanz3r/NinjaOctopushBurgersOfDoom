#include "Shader.h"
#include <fstream>

Shader::Shader(const char* filename, GLenum shaderType) {
	_shaderType = shaderType;

	std::string shader_string = readFile(filename);
	const char *shader_source = shader_string.c_str();

	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shader_source, nullptr);
	glCompileShader(shader);
}

Shader::~Shader() {
	glDeleteShader(shader);
}

GLuint Shader::shaderID() const {
	return shader;
}

GLenum Shader::shaderType() const {
	return _shaderType;
}

std::string Shader::readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		fputs("Could not read file:", stderr);
		fputs(filePath, stderr);
		fputs("\n", stderr);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}