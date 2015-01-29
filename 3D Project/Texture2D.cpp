#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_TGA
#include <stb_image.h>
#include "util.h"

Texture2D::Texture2D(const char* filename) {
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	// Load texture from file
	int components;
	unsigned char* data = stbi_load(filename, &_width, &_height, &components, 0);

	if (data == NULL) {
		fputs("Couldn't load image: ", stderr);
		util::log(filename);
	}

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, format(components), GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Generate mipmaps, by the way.
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &texID);
}

GLuint Texture2D::textureID() const {
	return texID;
}

int Texture2D::width() const {
	return _width;
}

int Texture2D::height() const {
	return _height;
}