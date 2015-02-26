#include "FrameBufferObjects.h"
#include "util.h"

FrameBufferObjects::FrameBufferObjects() {

}

FrameBufferObjects::~FrameBufferObjects() {
	if (fbo != 0)
		glDeleteFramebuffers(1, &fbo);

	if (mTextures[0] != 0)
		glDeleteTextures((sizeof(mTextures) / sizeof(mTextures[0])), mTextures);

	if (depthHandle != 0)
		glDeleteTextures(1, &depthHandle);
}

void FrameBufferObjects::begin(unsigned int width, unsigned int height) {
	// Create the FBO
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Generate textures
	glGenTextures((sizeof(mTextures) / sizeof(mTextures[0])), mTextures);
	glGenTextures(1, &depthHandle);

	// Check that internal format is supporeted by hardware
	glBindTexture(GL_TEXTURE_2D, mTextures[POSITION]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextures[POSITION], 0);

	glBindTexture(GL_TEXTURE_2D, mTextures[DIFFUSE]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mTextures[DIFFUSE], 0);

	glBindTexture(GL_TEXTURE_2D, mTextures[NORMAL]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mTextures[NORMAL], 0);

	// Bind depthHandle
	glBindTexture(GL_TEXTURE_2D, depthHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthHandle, 0);

	// Create and intialize draw buffers (output from geometry pass)
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers((sizeof(drawBuffers) / sizeof(drawBuffers[0])), drawBuffers);

	// Check if Framebuffer created correctly
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		util::log("Frame Buffer failed");

	// Defualt framebuffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void FrameBufferObjects::bindForWriting() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void FrameBufferObjects::bindForReading() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	for (unsigned int i = 0; i < (sizeof(mTextures) / sizeof(mTextures[0])); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mTextures[POSITION + i]);
	}
}

void FrameBufferObjects::bindForTexReading() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
}

void FrameBufferObjects::setReadBuffer(TEXTURE_TYPE texType){
	glReadBuffer(GL_COLOR_ATTACHMENT0 + texType);
}
