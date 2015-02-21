#include "FrameBufferObjects.h"
#include "util.h"


FrameBufferObjects::FrameBufferObjects(int width, int height)
{
	GLenum state;
	this->width = width;
	this->height = height;

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

	glGenRenderbuffers(1, &depthHandle);
	glBindRenderbuffer(GL_RENDERBUFFER, depthHandle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, this->width, this->height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthHandle);

	glGenRenderbuffers(1, &diffuseRenderTarget);
	glBindRenderbuffer(GL_RENDERBUFFER, diffuseRenderTarget);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, this->width, this->height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, diffuseRenderTarget);
	
	glGenRenderbuffers(1, &positionRenderTarget);
	glBindRenderbuffer(GL_RENDERBUFFER, positionRenderTarget);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA32F, this->width, this->height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, positionRenderTarget);

	glGenRenderbuffers(1, &normalRenderTarget);
	glBindRenderbuffer(GL_RENDERBUFFER, normalRenderTarget);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA32F, this->width, this->height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_RENDERBUFFER, normalRenderTarget);

	glGenTextures(1, &diffuseTex);
	glBindTexture(GL_TEXTURE_2D, diffuseTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, diffuseTex, 0);

	// Generate and bind the OGL texture for positions
	glGenTextures(1, &positionTex);
	glBindTexture(GL_TEXTURE_2D, positionTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, this->width, this->height, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Attach the texture to the FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, positionTex, 0);

	// Generate and bind the OGL texture for normals
	glGenTextures(1, &normalTex);
	glBindTexture(GL_TEXTURE_2D, normalTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->width, this->height, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Attach the texture to the FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, normalTex, 0);

	state = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (state!=GL_FRAMEBUFFER_COMPLETE)
		util::log("Frame Buffer Objects failed");
	//unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

};
FrameBufferObjects::~FrameBufferObjects()
{
	glDeleteTextures(1, &positionTex);
	glDeleteTextures(1, &normalTex);
	glDeleteTextures(1, &diffuseRenderTarget);
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &diffuseRenderTarget);
	glDeleteRenderbuffers(1, &normalRenderTarget);
	glDeleteRenderbuffers(1, &depthHandle);
	glDeleteRenderbuffers(1, &normalRenderTarget);
};

GLuint FrameBufferObjects::getPositionTex() const{ return positionTex; };
GLuint FrameBufferObjects::getDiffuseTex() const{ return diffuseTex; };
GLuint FrameBufferObjects::getNormalTex() const{ return normalTex; };

void FrameBufferObjects::begin()
{
	// Bind our FBO and set the viewport to the proper size
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

	// Specify what to render an start acquiring
	GLenum buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, buffers);
};
void FrameBufferObjects::end()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glPopAttrib();
};
void FrameBufferObjects::showTexture(unsigned int i, float fSizeX, float fSizeY, float x, float y) const {
	GLuint texture = diffuseTex;
	if (i == 1) texture = positionTex;
	else
	if (i == 2) texture = normalTex;

	//Render a quad and attach the textures + draw.
}
