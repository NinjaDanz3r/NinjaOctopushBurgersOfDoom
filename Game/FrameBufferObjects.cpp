#include "FrameBufferObjects.h"
#include "util.h"

FrameBufferObjects::FrameBufferObjects() {

}

FrameBufferObjects::~FrameBufferObjects() {
	if (fbo != 0)
		glDeleteFramebuffers(1, &fbo);

	if (mTextures[0] != 0)
		glDeleteTextures(NUM_TEXTURES, mTextures);

	if (depthHandle != 0)
		glDeleteTextures(1, &depthHandle);
}

void FrameBufferObjects::begin(unsigned int width, unsigned int height) {
	// Create the FBO
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Generate textures
	glGenTextures(NUM_TEXTURES, mTextures);
	glGenTextures(1, &depthHandle);
	
	for (unsigned int i = 0; i < NUM_TEXTURES; i++)
		attachTexture(mTextures[i], width, height, GL_COLOR_ATTACHMENT0 + i);

	// Bind depthHandle
	glBindTexture(GL_TEXTURE_2D, depthHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthHandle, 0);

	// Create and intialize draw buffers (output from geometry pass)
	GLenum drawBuffers[NUM_TEXTURES];
	for (unsigned int i = 0; i < NUM_TEXTURES; i++)
		drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
	glDrawBuffers(NUM_TEXTURES, drawBuffers);

	// Check if framebuffer created correctly
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		util::log("Frame Buffer failed");

	// Default framebuffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

GLuint FrameBufferObjects::texture(TEXTURE_TYPE textureType) const {
	return mTextures[textureType];
}

void FrameBufferObjects::bindForWriting() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void FrameBufferObjects::bindForReading() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	for (unsigned int i = 0; i < NUM_TEXTURES; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mTextures[i]);
	}
}

void FrameBufferObjects::bindForTexReading() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
}

void FrameBufferObjects::setReadBuffer(TEXTURE_TYPE textureType){
	glReadBuffer(GL_COLOR_ATTACHMENT0 + textureType);
}

void FrameBufferObjects::attachTexture(GLuint texture, unsigned int width, unsigned int height, GLenum attachment) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, 0);
}