#include "TextureResource.h"
#include "Texture2D.h"
#include "util.h"

TextureResource::TextureResource(const std::string &name, std::string directory) {
	this->name = name;
	texture = new Texture2D((directory + "/Textures/" + name + ".tga").c_str());
}

TextureResource::TextureResource(std::ifstream &file, std::string directory) {
	this->name = util::readString(file);
	texture = new Texture2D((directory + "/Textures/" + name + ".tga").c_str());
}

TextureResource::~TextureResource() {
	delete texture;
}

void TextureResource::save(std::ofstream &file) const {
	util::writeString(file, name);
}