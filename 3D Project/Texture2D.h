#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#include "Texture.h"

/// A two-dimensional texture.
/**
 * Used to load a 2D texture from an image file.
 */
class Texture2D : public Texture {
	public:
		/// Create new texture from the given image file.
		/**
		 * Supported image formats: TGA.
		 * @param filename Filename (relative or absolute) of the image file.
		 */
		Texture2D(const char* filename);

		/// Destructor
		~Texture2D();

		/// Get OpenGL texture ID.
		/**
		* Used when binding a texture before draw calls.
		* @return The OpenGL texture identifier
		*/
		GLuint textureID() const;

		/// Get the width of the texture.
		/**
		* @return The width of the texture in texels
		*/
		int width() const;

		/// Get the height of the texture.
		/**
		* @return The height of the texture in texels
		*/
		int height() const;

	private:
		GLuint texID;
		int _width, _height;
};

#endif