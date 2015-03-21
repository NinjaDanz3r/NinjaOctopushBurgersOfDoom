#ifndef __SHADOWMAP_H__
#define __SHADOWMAP_H__

#include <GL/glew.h>

class ShadowMap {
	public:
		/// Constructor
		/**
		* @param width Width of the context.
		* @param height Height of the context.
		*/
		ShadowMap(unsigned int width, unsigned int height);
		
		/// Destructor
		/**
		* Free allocated resources.
		*/
		~ShadowMap();

		/// Enable frame buffer object for writing.
		void bindForWriting();

		/// Enable frame buffer object for reading.
		void bindForReading(GLenum texture);

	private:
		GLuint fbo;
		GLuint shadowMap;
};

#endif