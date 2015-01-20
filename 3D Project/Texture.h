#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <gl/glew.h>
#include <gl/GL.h>

// Represents a 2D-texture.
class Texture {
	public:
		// Create new texture from the given image file.
		Texture(const char* filename);

		// Destructor
		~Texture();

		// Get OpenGL texture ID.
		GLuint textureID() const;

		// Get the width of the texture.
		int width() const;

		// Get the height of the texture.
		int height() const;

	private:
		GLuint texID;
		unsigned char* data;
		int _width, _height;
};

#endif