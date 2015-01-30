#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#include "Texture.h"

class Texture2D : public Texture {
	public:
		// Create new texture from the given image file.
		Texture2D(const char* filename);

		// Destructor
		~Texture2D();

		// Get OpenGL texture ID.
		GLuint textureID() const;

		// Get the width of the texture.
		int width() const;

		// Get the height of the texture.
		int height() const;

	private:
		GLuint texID;
		int _width, _height;
};

#endif