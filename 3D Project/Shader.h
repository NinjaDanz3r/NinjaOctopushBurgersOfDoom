#ifndef __SHADER_H__
#define __SHADER_H__

#include <gl/glew.h>
#include <gl/GL.h>
#include <string>

class Shader {
	public:
		// Constructor
		Shader(const char* filename, GLenum shaderType);

		// Destructor
		~Shader();

		// Get shader ID.
		GLuint shaderID() const;

		// Get shader type.
		GLenum shaderType() const;

	private:
		// Helper method to read a file to a std::string.
		static std::string readFile(const char *filePath);

		GLuint shader;
		GLenum _shaderType;
};

#endif