#ifndef __CUBEMAPTEXTURE_H__
#define __CUBEMAPTEXTURE_H__

#include "Texture.h"

// Represents a cube map. Used for skyboxes.
class CubeMapTexture : public Texture {
	public:
		// Constructor
		CubeMapTexture(const char* posXFilename, const char* negXFilename, const char* posYFilename, const char* negYFilename, const char* posZFilename, const char* negZFilename);

		// Destructor
		~CubeMapTexture();

		// Get OpenGL texture ID.
		GLuint textureID() const;

		// Get the width of the texture.
		int width() const;

		// Get the height of the texture.
		int height() const;

	private:
		GLuint texID;
		int _width, _height;

		static GLenum targets[6];
};

#endif