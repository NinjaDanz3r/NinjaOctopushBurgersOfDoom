#include "FrameBufferObjects.h"
#include "util.h"


FrameBufferObjects::FrameBufferObjects(int width, int height)
{

	//UPDATE THIS!
	GLenum state;
	this->width = width;
	this->height = height;

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

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
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA32F_ARB, this->width, this->height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, positionRenderTarget);

	glGenRenderbuffers(1, &normalRenderTarget);
	glBindRenderbuffer(GL_RENDERBUFFER, normalRenderTarget);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA32F_ARB, this->width, this->height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_RENDERBUFFER, normalRenderTarget);

	//UPDATE THIS!!!
	glGenTextures(1, &diffuseTex);
	glBindTexture(GL_TEXTURE_2D, diffuseTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, diffuseTex, 0);

	// Generate and bind the OGL texture for positions
	glGenTextures(1, &positionTex);
	glBindTexture(GL_TEXTURE_2D, positionTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, this->width, this->height, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Attach the texture to the FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, positionTex, 0);

	// Generate and bind the OGL texture for normals
	glGenTextures(1, &normalTex);
	glBindTexture(GL_TEXTURE_2D, normalTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, this->width, this->height, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Attach the texture to the FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, normalTex, 0);

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
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0, 0, this->width, this->height);

	// Clear the render targets
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);

	// Specify what to render an start acquiring
	GLenum buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, buffers);
};
void FrameBufferObjects::end()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glPopAttrib();
};
void FrameBufferObjects::showTexture(unsigned int i, float fSizeX, float fSizeY, float x, float y) const {
	GLuint texture = diffuseTex;
	if (i == 1) texture = positionTex;
	else
	if (i == 2) texture = normalTex;

	//Projection setup
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, width, 0, height, 0.1f, 2);

	//Model setup
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Render the quad
	glLoadIdentity();
	glTranslatef(x, -y, -1.0);

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, (float)height, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, height - fSizeY, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(fSizeX, height - fSizeY, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(fSizeX, (float)height, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	//Reset to the matrices	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
