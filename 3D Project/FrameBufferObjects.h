#ifndef __FRAMEBUFFEROBJECTS_H__
#define __FRAMEBUFFEROBJECTS_H__

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

//#define POSITION_TEXTURE 0
//#define DIFFUSE_TEXTURE  1
//#define NORMAL_TEXTURE  2

class FrameBufferObjects
{
public:	
	/// Defines the position of each texture and the number of textures
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
	GLuint getPositionTex()const{ return m_textures[POSITION]; };
	GLuint getDiffuseTex() const{ return m_textures[DIFFUSE]; };
	GLuint getNormalTex() const{ return m_textures[NORMAL]; };
	
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
	GLuint m_textures[NUM_TEXTURES];

	GLuint fbo;
	GLuint depthHandle;

	unsigned int width;
	unsigned int height;
};

#endif
