#include "FrameBufferObjects.h"
#include "util.h"


FrameBufferObjects::FrameBufferObjects()
{
	fbo = 0;
	depthHandle = 0;
	memset(m_textures,0, sizeof(m_textures));
}
FrameBufferObjects::~FrameBufferObjects()
{
	if (fbo != 0) {
		glDeleteFramebuffers(1, &fbo);
	}

	if (m_textures[0] != 0) {
		glDeleteTextures((sizeof(m_textures) / sizeof(m_textures[0])), m_textures);
	}

	if (depthHandle != 0) {
		glDeleteTextures(1, &depthHandle);
	}
}
bool FrameBufferObjects::begin(unsigned int width, unsigned int height)
{
	// Create the FBO
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Create the gbuffer textures
	glGenTextures((sizeof(m_textures) / sizeof(m_textures[0])), m_textures);
	glGenTextures(1, &depthHandle);

	for (unsigned int i = 0; i < (sizeof(m_textures) / sizeof(m_textures[0])); i++) {
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
	}

	// depth
	glBindTexture(GL_TEXTURE_2D, depthHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthHandle, 0);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2};

	glDrawBuffers((sizeof(DrawBuffers) / sizeof(DrawBuffers[0])), DrawBuffers);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		printf("FB error, status: 0x%x\n", Status);
		return false;
	}

	// restore default FBO
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	return true;
}
void FrameBufferObjects::bindForWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void FrameBufferObjects::bindForReading()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	for (unsigned int i = 0; i < (sizeof(m_textures) / sizeof(m_textures[0])); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION + i]);
	}
}
void FrameBufferObjects::bindForTexReading()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
}
void FrameBufferObjects::setReadBuffer(GBUFFER_TEXTURE_TYPE texType){
	glReadBuffer(GL_COLOR_ATTACHMENT0 + texType);
}

