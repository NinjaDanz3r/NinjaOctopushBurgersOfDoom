#ifndef __FRAMEBUFFEROBJECTS_H__
#define __FRAMEBUFFEROBJECTS_H__

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

/// Holds the frame buffers used for deferred rendering.
class FrameBufferObjects {
	public:
		/// Defines the position of each texture and the number of textures.
		enum TEXTURE_TYPE {
			POSITION,
			DIFFUSE,
			NORMAL,
			NUM_TEXTURES
		};

		/// Constructor
		/**
		* @param width Width of the context.
		* @param height Height of the context.
		*/
		FrameBufferObjects(unsigned int width, unsigned int height);

		/// Destructor
		/**
		* Free allocated resources.
		*/
		~FrameBufferObjects();

		/// Get texture.
		/**
		 * @param textureType The type of texture to get.
		 * @return The texture identifier
		 */
		GLuint texture(TEXTURE_TYPE textureType) const;

		/// Enable frame buffer object for writing.
		void bindForWriting();

		/// Enable frame buffer object for reading.
		void bindForReading();

		/// Enable frame buffer object for reading textures.
		void bindForTexReading();

		/// Set buffer to read from.
		/**
		 * @param textureType Texture type of the buffer to read from.
		 */
		void setReadBuffer(TEXTURE_TYPE textureType);

	private:
		static void attachTexture(GLuint texture, unsigned int width, unsigned int height, GLenum attachment);

		GLuint mTextures[NUM_TEXTURES];

		GLuint fbo;
		GLuint depthHandle;

		unsigned int width;
		unsigned int height;
};

#endif
