#include "CubeMapTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_TGA
#include <stb_image.h>
#include <util.h>

GLenum CubeMapTexture::targets[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

CubeMapTexture::CubeMapTexture(const char* posXFilename, const char* negXFilename, const char* posYFilename, const char* negYFilename, const char* posZFilename, const char* negZFilename) {
	const char* filenames[6] = { posXFilename, negXFilename, posYFilename, negYFilename, posZFilename, negZFilename };

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

	// Load texture from image files.
	for (int i = 0; i < 6; i++) {
		int components;
		unsigned char* data = stbi_load(filenames[i], &_width, &_height, &components, 0);

		if (data == NULL) {
			fputs("Couldn't load image: ", stderr);
			util::log(filenames[i]);
		}

		glTexImage2D(targets[i], 0, GL_RGB, _width, _height, 0, format(components), GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	// Set texture properties.
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

CubeMapTexture::~CubeMapTexture() {
	glDeleteTextures(1, &texID);
}

GLuint CubeMapTexture::textureID() const {
	return texID;
}

int CubeMapTexture::width() const {
	return _width;
}

int CubeMapTexture::height() const {
	return _height;
}