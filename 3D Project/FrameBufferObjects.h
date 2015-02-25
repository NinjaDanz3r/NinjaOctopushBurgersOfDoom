#ifndef __FRAMEBUFFEROBJECTS_H__
#define __FRAMEBUFFEROBJECTS_H__

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#define GBUFFER_POSITION_TEXTURE_UNIT 0
#define GBUFFER_DIFFUSE_TEXTURE_UNIT  1
#define GBUFFER_NORMAL_TEXTURE_UNIT   2
#define GBUFFER_TEXCOORD_TEXTURE_UNIT 3

class FrameBufferObjects
{
public:	
	enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_NUM_TEXTURES
	};
	//Construct/destruct
	FrameBufferObjects();
	~FrameBufferObjects();

	GLuint getPositionTex()const{ return m_textures[GBUFFER_TEXTURE_TYPE_POSITION]; } ;
	GLuint getDiffuseTex() const{ return m_textures[GBUFFER_TEXTURE_TYPE_DIFFUSE]; };
	GLuint getNormalTex() const{ return m_textures[GBUFFER_TEXTURE_TYPE_NORMAL]; };
	
	void bindForWriting();
	void bindForReading();
	void bindForTexReading();
	void setReadBuffer(GBUFFER_TEXTURE_TYPE texType);

	bool begin(unsigned int width, unsigned int height);
private:

	GLuint m_textures[GBUFFER_NUM_TEXTURES];

	//GL IDs
	GLuint fbo;
	GLuint depthHandle;

	//FBO info
	unsigned int width;
	unsigned int height;
};

#endif
