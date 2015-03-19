#ifndef __SHADOWMAPPING_H__
#define __SHADOWMAPPING_H__

#include<GL/glew.h>

class ShadowMapping {
	public:
		/// Constructor
		/**
		* @param width Width of the context.
		* @param height Height of the context.
		*/
		ShadowMapping(unsigned int width, unsigned int height);
		
		/// Destructor
		/**
		* Free allocated resources.
		*/
		~ShadowMapping();

		/// Enable frame buffer object for writing.
		void bindForWriting();

		/// Enable frame buffer object for reading.
		void bindForReading(GLenum texture);

	private:
		GLuint fbo;
		GLuint shadowMap;
};

#endif