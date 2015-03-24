#include "FrameBufferObjects.h"

#include <util.h>
#include <ShaderProgram.h>
#include "Camera.h"

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

const glm::vec2 FrameBufferObjects::vertices[4] = { { -1.f, 1.f }, { 1.f, 1.f }, { -1.f, -1.f }, { 1.f, -1.f } };
const unsigned int FrameBufferObjects::indices[6] = { 0, 1, 3, 0, 3, 2 };

FrameBufferObjects::FrameBufferObjects(ShaderProgram* shaderProgram, unsigned int width, unsigned int height) {
	this->shaderProgram = shaderProgram;
	this->width = width;
	this->height = height;

	// Create the FBO
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Generate textures
	glGenTextures(NUM_TEXTURES, mTextures);
	glGenTextures(1, &depthHandle);

	attachTexture(mTextures[DIFFUSE], width, height, GL_COLOR_ATTACHMENT0 + DIFFUSE, GL_RGB);
	attachTexture(mTextures[NORMAL], width, height, GL_COLOR_ATTACHMENT0 + NORMAL, GL_RGB16F);
	attachTexture(mTextures[SPECULAR], width, height, GL_COLOR_ATTACHMENT0 + SPECULAR, GL_RGB);

	// Bind depthHandle
	glBindTexture(GL_TEXTURE_2D, depthHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
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

	shaderProgram->use();
	bindQuad();
}

FrameBufferObjects::~FrameBufferObjects() {
	if (fbo != 0)
		glDeleteFramebuffers(1, &fbo);

	if (mTextures[0] != 0)
		glDeleteTextures(NUM_TEXTURES, mTextures);

	if (depthHandle != 0)
		glDeleteTextures(1, &depthHandle);

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

GLuint FrameBufferObjects::texture(TEXTURE_TYPE textureType) const {
	return mTextures[textureType];
}

void FrameBufferObjects::bindForWriting() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void FrameBufferObjects::bindForReading() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);

	for (unsigned int i = 0; i < NUM_TEXTURES; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mTextures[i]);
	}

	glActiveTexture(GL_TEXTURE0 + NUM_TEXTURES);
	glBindTexture(GL_TEXTURE_2D, depthHandle);
}

void FrameBufferObjects::bindForTexReading() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
}

void FrameBufferObjects::setReadBuffer(TEXTURE_TYPE textureType){
	glReadBuffer(GL_COLOR_ATTACHMENT0 + textureType);
}

void FrameBufferObjects::showTextures(int width, int height) {
	// Disable depth testing
	GLboolean depthTest = glIsEnabled(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);

	int halfWidth = width / 2;
	int halfHeight = height / 2;

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	bindForTexReading();

	setReadBuffer(FrameBufferObjects::DIFFUSE);
	glBlitFramebuffer(0, 0, width, height, 0, 0, halfWidth, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	setReadBuffer(FrameBufferObjects::NORMAL);
	glBlitFramebuffer(0, 0, width, height, 0, halfHeight, halfWidth, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	setReadBuffer(FrameBufferObjects::SPECULAR);
	glBlitFramebuffer(0, 0, width, height, halfWidth, halfHeight, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	if (depthTest)
		glEnable(GL_DEPTH_TEST);
}

void FrameBufferObjects::render(Camera* camera, int width, int height) {
	// Disable depth testing
	GLboolean depthTest = glIsEnabled(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);

	GLint oldDepthFunctionMode;
	glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFunctionMode);
	glDepthFunc(GL_ALWAYS);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	shaderProgram->use();

	// Blending enabled for handling multiple light sources
	GLboolean blend = glIsEnabled(GL_BLEND);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	bindLighting(camera, width, height);
	bindForReading();

	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);

	if (!depthTest)
		glDisable(GL_DEPTH_TEST);
	if (!blend)
		glDisable(GL_BLEND);

	glDepthFunc(oldDepthFunctionMode);
}

void FrameBufferObjects::attachTexture(GLuint texture, unsigned int width, unsigned int height, GLenum attachment, GLint internalFormat) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, 0);
}

void FrameBufferObjects::bindLighting(Camera* camera, int width, int height){
	// Bind light information for lighting pass
	glm::mat4 view = camera->view();

	glm::vec2 screenSize(width, height);

	glUniform1i(shaderProgram->uniformLocation("tDiffuse"), FrameBufferObjects::DIFFUSE);
	glUniform1i(shaderProgram->uniformLocation("tNormals"), FrameBufferObjects::NORMAL);
	glUniform1i(shaderProgram->uniformLocation("tSpecular"), FrameBufferObjects::SPECULAR);
	glUniform1i(shaderProgram->uniformLocation("tDepth"), FrameBufferObjects::NUM_TEXTURES);

	glUniform2fv(shaderProgram->uniformLocation("screenSize"), 1, &screenSize[0]);
	glUniform4fv(shaderProgram->uniformLocation("lightPosition"), 1, &(view * light.position)[0]);
	glUniform3fv(shaderProgram->uniformLocation("lightIntensity"), 1, &light.intensity[0]);
	glUniform3fv(shaderProgram->uniformLocation("diffuseKoefficient"), 1, &light.diffuseKoefficient[0]);

	glUniformMatrix4fv(shaderProgram->uniformLocation("inverseProjectionMatrix"), 1, GL_FALSE, &glm::inverse(camera->projection(width, height))[0][0]);
}

void FrameBufferObjects::bindQuad() {
	vertexCount = 4;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);

	// Define vertex data layout
	glGenVertexArrays(1, &vertexAttribute);
	glBindVertexArray(vertexAttribute);
	glEnableVertexAttribArray(0);

	GLuint vertexPos = shaderProgram->attributeLocation("vertex_position");
	glVertexAttribPointer(vertexPos, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), BUFFER_OFFSET(0));

	// Index buffer
	indexCount = 6;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}