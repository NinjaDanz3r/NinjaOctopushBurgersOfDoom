#include "ShadowMapping.h"
#include "util.h"


ShadowMapping::ShadowMapping()
{
	fbo = 0;
	shadowMap = 0;
	depth = 0;
}
ShadowMapping::~ShadowMapping()
{
	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &shadowMap);
	glDeleteTextures(1, &depth);

}
void ShadowMapping::begin(unsigned int width, unsigned int height)
{
	glGenFramebuffers(1, &fbo);

	glGenTextures(1, &depth);
	glBindTexture(GL_TEXTURE_2D, depth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int i = 0; i < 6; i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, NULL);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth, 0);

	// Disable writes to the color buffer
	glDrawBuffer(GL_NONE);

	// Disable reads from the color buffer
	glReadBuffer(GL_NONE);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		util::log("Shadow mapping FB failed \n");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


}
void ShadowMapping::bindForWriting(GLenum cubeFace)
{
	//What color attatchment to use.
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, cubeFace, shadowMap, 0);
	glDrawBuffer(GL_COLOR_ATTACHMENT3);
}
void ShadowMapping::bindForReading(GLenum texture)
{
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);
}