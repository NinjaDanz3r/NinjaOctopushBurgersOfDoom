#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_TGA
#include <stb_image.h>
#include "util.h"

Texture::Texture(const char* filename) {
	// Create one OpenGL texture
	glGenTextures(1, &texID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texID);

	// Load texture from file
	int components;
	data = stbi_load(filename, &_width, &_height, &components, 0);

	if (data == NULL) {
		fputs("Couldn't load image: ", stderr);
		util::log(filename);
	}

	// Get which format the image is in
	GLenum format;
	switch (components) {
	case 1:
		format = GL_RED;
		break;
	case 2:
		format = GL_RG;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	}

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, format, GL_UNSIGNED_BYTE, data);

	// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Generate mipmaps, by the way.
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
	glDeleteTextures(1, &texID);
	stbi_image_free(data);
}

GLuint Texture::textureID() const {
	return texID;
}

int Texture::width() const {
	return _width;
}

int Texture::height() const {
	return _height;
}