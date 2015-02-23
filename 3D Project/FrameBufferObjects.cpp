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
	/*GLenum state;
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
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, diffuseTex, 0);

	// Generate and bind the OGL texture for positions
	glGenTextures(1, &positionTex);
	glBindTexture(GL_TEXTURE_2D, positionTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, this->width, this->height, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Attach the texture to the FBO
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, positionTex, 0);

	// Generate and bind the OGL texture for normals
	glGenTextures(1, &normalTex);
	glBindTexture(GL_TEXTURE_2D, normalTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->width, this->height, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Attach the texture to the FBO
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, normalTex, 0);

	state = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (state!=GL_FRAMEBUFFER_COMPLETE)
	util::log("Frame Buffer Objects failed");
	//unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);*/
	// Create the FBO
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Create the gbuffer textures
	glGenTextures((sizeof(m_textures) / sizeof(m_textures[0])), m_textures);
	glGenTextures(1, &depthHandle);

	for (unsigned int i = 0; i < (sizeof(m_textures) / sizeof(m_textures[0])); i++) {
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
	}

	// depth
	glBindTexture(GL_TEXTURE_2D, depthHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthHandle, 0);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3 };

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

