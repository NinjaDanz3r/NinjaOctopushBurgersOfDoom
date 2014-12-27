#ifndef __SHADERS_H__
#define __SHADERS_H__

#include <gl/glew.h>
#include <gl/GL.h>
#include <string>

// Handles shaders.
class Shaders {
	public:
		// Create new shaders from the specified files.
		Shaders(std::string shaderName);

		// Destructor
		virtual ~Shaders();

		// Get shader program.
		GLuint shaderProgram() const;

		// Get base image location.
		GLuint baseImageLocation() const;

		// Get Model matrix location.
		GLuint modelLocation() const;

		// Get View matrix location.
		GLuint viewLocation() const;

		// Get Normal matrix location.
		GLuint normalLocation() const;

		// Get Projection matrix location.
		GLuint projectionLocation() const;

		// Get MVP Matrix location.
		GLuint MVPLocation() const;

		// Get light position location.
		GLuint lightPositionLocation() const;

		// Get light intensity location.
		GLuint lightIntensityLocation() const;

		// Get diffuse koefficient location.
		GLuint diffuseKoefficientLocation() const;

	private:
		// Helper method to read a file to a std::string.
		std::string readFile(const char *filePath);

		// Helper method to check and print compile errors (if there are any).
		void checkCompileErrors(GLuint shader);

		// Helper method to check and print link errors (if there are any).
		void checkLinkErrors(GLuint program);

		GLuint gShaderProgram = 0;
		GLuint baseImageLoc;
		GLuint modelLoc;
		GLuint viewLoc;
		GLuint normalLoc;
		GLuint projectionLoc;
		GLuint lightPositionLoc;
		GLuint lightIntensityLoc;
		GLuint diffuseKoefficientLoc;

		// Vertex shader.
		GLuint vs;
		// Geometry shader.
		GLuint gs;
		// Fragment shader.
		GLuint fs;
};

#endif