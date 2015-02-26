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
		FrameBufferObjects();

		/// Destructor
		/**
		* Free allocated resources.
		*/
		~FrameBufferObjects();

		/// Get textures
		GLuint getPositionTex() const{ return mTextures[POSITION]; };
		GLuint getDiffuseTex() const{ return mTextures[DIFFUSE]; };
		GLuint getNormalTex() const{ return mTextures[NORMAL]; };

		/// Enable fbo for writing
		void bindForWriting();

		/// Enable fbo for reading
		void bindForReading();

		/// Enable fbo for reading textures
		void bindForTexReading();

		/// Set buffer to read from
		void setReadBuffer(TEXTURE_TYPE texType);

		/// Initializes fbo, depth handle and textures
		/**
		* @param width Width of the context.
		* @param height Height of the context.
		*/
		void begin(unsigned int width, unsigned int height);

	private:
		GLuint mTextures[NUM_TEXTURES];

		GLuint fbo;
		GLuint depthHandle;

		unsigned int width;
		unsigned int height;
};

#endif
