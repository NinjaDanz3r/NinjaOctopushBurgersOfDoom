#ifndef __SHADOWMAPPING_H__
#define __SHADOWMAPPING_H__

#include<GL/glew.h>

class ShadowMapping
{
public:
	ShadowMapping();
	~ShadowMapping();

	void begin(unsigned int width, unsigned int height);
	void bindForWriting(GLenum cubeFace);
	void bindForReading(GLenum texture);
private:
	GLuint fbo;
	GLuint shadowMap;
	GLuint depth;
};
#endif
