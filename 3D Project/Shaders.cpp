#include "Shaders.h"
#include <fstream>
#include <iostream>
#include <vector>

Shaders::Shaders(std::string shaderName) {
	std::string vertex_shader_string = readFile((shaderName + "_vertex.glsl").c_str());
	std::string geometry_shader_string = readFile((shaderName + "_geometry.glsl").c_str());
	std::string fragment_shader_string = readFile((shaderName + "_fragment.glsl").c_str());

	const char *vertex_shader = vertex_shader_string.c_str();
	const char *geometry_shader = geometry_shader_string.c_str();
	const char *fragment_shader = fragment_shader_string.c_str();

	// Create vertex shader
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, nullptr);
	glCompileShader(vs);

	// Create geometry shader
	gs = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(gs, 1, &geometry_shader, nullptr);
	glCompileShader(gs);

	// Create fragment shader
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);

	// Link shader program (connect vs and ps)
	gShaderProgram = glCreateProgram();
	glAttachShader(gShaderProgram, vs);
	glAttachShader(gShaderProgram, gs);
	glAttachShader(gShaderProgram, fs);
	glLinkProgram(gShaderProgram);

	// Uniform locations.
	baseImageLoc = glGetUniformLocation(gShaderProgram, "baseImage");
	modelLoc = glGetUniformLocation(gShaderProgram, "modelMatrix");
	viewLoc = glGetUniformLocation(gShaderProgram, "viewMatrix");
	normalLoc = glGetUniformLocation(gShaderProgram, "normalMatrix");
	projectionLoc = glGetUniformLocation(gShaderProgram, "projectionMatrix");
	lightPositionLoc = glGetUniformLocation(gShaderProgram, "lightPosition");
	lightIntensityLoc = glGetUniformLocation(gShaderProgram, "lightIntensity");
	diffuseKoefficientLoc = glGetUniformLocation(gShaderProgram, "diffuseKoefficient");
}

Shaders::~Shaders() {
	glDeleteProgram(gShaderProgram);
	glDeleteShader(vs);
	glDeleteShader(gs);
	glDeleteShader(fs);
}

GLuint Shaders::shaderProgram() const {
	return gShaderProgram;
}

GLuint Shaders::baseImageLocation() const {
	return baseImageLoc;
}

GLuint Shaders::modelLocation() const {
	return modelLoc;
}

GLuint Shaders::viewLocation() const {
	return viewLoc;
}

GLuint Shaders::normalLocation() const {
	return normalLoc;
}

GLuint Shaders::projectionLocation() const {
	return projectionLoc;
}

GLuint Shaders::lightPositionLocation() const {
	return lightPositionLoc;
}

GLuint Shaders::lightIntensityLocation() const {
	return lightIntensityLoc;
}

GLuint Shaders::diffuseKoefficientLocation() const {
	return diffuseKoefficientLoc;
}

std::string Shaders::readFile(const char *filePath) {
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