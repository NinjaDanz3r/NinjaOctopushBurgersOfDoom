#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <gl/glew.h>
#include <gl/GL.h>

// Represents a 2D-texture.
class Texture {
	public:
		// Create new texture.
		Texture();

		// Destructor
		~Texture();

		// Get OpenGL texture ID.
		GLuint textureID() const;

	private:
		GLuint texID;
		unsigned char* data;
};

#endif