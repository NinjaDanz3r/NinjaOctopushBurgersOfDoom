#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <gl/glew.h>
#include <gl/GL.h>

// Represents a texture.
class Texture {
	public:
		// Constructor
		Texture() { }

		// Destructor
		virtual ~Texture() { }

		// Get OpenGL texture ID.
		virtual GLuint textureID() const = 0;

		// Get the width of the texture.
		virtual int width() const = 0;

		// Get the height of the texture.
		virtual int height() const = 0;

		// Get image GL format based on color components.
		static GLenum format(int components);
};

#endif