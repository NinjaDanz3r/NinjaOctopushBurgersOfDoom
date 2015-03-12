#include "ShadowMapping.h"
#include "util.h"


ShadowMapping::ShadowMapping()
{
	fbo = 0;
	shadowMap = 0;
}
ShadowMapping::~ShadowMapping()
{
	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &shadowMap);
}
void ShadowMapping::begin(unsigned int width, unsigned int height)
{
	glGenFramebuffers(1, &fbo);

	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

	// Disable writes to the color buffer
	glDrawBuffer(GL_NONE);

	// Disable reads from the color buffer
	glReadBuffer(GL_NONE);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		util::log("Shadow mapping FB failed \n");
	}

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);


}
void ShadowMapping::bindForWriting()
{
	//What color attatchment to use.
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}
void ShadowMapping::bindForReading(GLenum texture)
{
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
}