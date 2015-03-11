#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#include "Texture.h"

/** @ingroup core
 * @{
 */

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
		CORE_EXPORT Texture2D(const char* filename);

		/// Destructor
		CORE_EXPORT ~Texture2D();

		/// Get OpenGL texture ID.
		/**
		 * Used when binding a texture before draw calls.
		 * @return The OpenGL texture identifier
		 */
		CORE_EXPORT GLuint textureID() const;

		/// Get the width of the texture.
		/**
		 * @return The width of the texture in texels
		 */
		CORE_EXPORT int width() const;

		/// Get the height of the texture.
		/**
		 * @return The height of the texture in texels
		 */
		CORE_EXPORT int height() const;

	private:
		GLuint texID;
		int _width, _height;
};

/** @} */

#endif