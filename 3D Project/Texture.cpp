#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_TGA
#include <stb_image.h>
#include "util.h"

Texture::Texture() {
	// Create one OpenGL texture
	glGenTextures(1, &texID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texID);

	// Load texture from file
	int width, height, comp;
	data = stbi_load("Resources/Textures/bth_image.tga", &width, &height, &comp, 0);

	if (data == NULL) {
		util::log("Couldn't load image: Resources/Textures/bth_image.tga");
	}

	// Get which format the image is in
	GLenum format;
	switch (comp) {
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);

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