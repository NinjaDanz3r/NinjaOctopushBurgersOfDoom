#ifndef __CUBEMAPTEXTURE_H__
#define __CUBEMAPTEXTURE_H__

#include <Texture.h>

/// A cubemap texture.
/**
 * A Cubemap %Texture is a texture composed of 6 2D images. The images are arranged in a cube-shape, hence the name. Used for skyboxes.
 * @see Skybox
 * @see <a href="https://www.opengl.org/wiki/Cubemap_Texture">OpenGL Cubemap Texture</a>
 */
class CubeMapTexture : public Texture {
	public:
		/// Create new texture from the given image files.
		/**
		 * Supported file formats: TGA.
		 * @param posXFilename Filename (relative or absolute) to the image file for the positive X face.
		 * @param negXFilename Filename (relative or absolute) to the image file for the negative X face.
		 * @param posYFilename Filename (relative or absolute) to the image file for the positive Y face.
		 * @param negYFilename Filename (relative or absolute) to the image file for the negative Y face.
		 * @param posZFilename Filename (relative or absolute) to the image file for the positive Z face.
		 * @param negZFilename Filename (relative or absolute) to the image file for the negative Z face.
		 */
		CubeMapTexture(const char* posXFilename, const char* negXFilename, const char* posYFilename, const char* negYFilename, const char* posZFilename, const char* negZFilename);

		/// Destructor
		~CubeMapTexture();

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

		static GLenum targets[6];
};

#endif