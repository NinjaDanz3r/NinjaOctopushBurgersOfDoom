#ifndef __FRAMEBUFFEROBJECTS_H__
#define __FRAMEBUFFEROBJECTS_H__

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

class FrameBufferObjects
{
public:
	//Construct/destruct
	FrameBufferObjects(int width, int height);
	~FrameBufferObjects();

	void showTexture(unsigned int i, float fSizeX, float fSizeY, float x, float y) const;
	GLuint getPositionTex() const;
	GLuint getDiffuseTex() const;
	GLuint getNormalTex() const;

	void begin();
	void end();
private:
	//GL IDs
	GLuint fbo;
	GLuint diffuseRenderTarget;
	GLuint normalRenderTarget;
	GLuint positionRenderTarget;
	GLuint depthHandle;

	//FBO info
	unsigned int width;
	unsigned int height;

	//Textures
	unsigned int diffuseTex;
	unsigned int positionTex;
	unsigned int normalTex;
};

#endif
