#include "TextureResource.h"
#include "Texture2D.h"
#include "util.h"

TextureResource::TextureResource(const std::string &name, std::string directory) {
	this->name = name;
	_texture = new Texture2D((directory + '/' + name + ".tga").c_str());
}

TextureResource::TextureResource(std::ifstream &file, std::string directory) {
	this->name = util::readString(file);
	_texture = new Texture2D((directory + '/' + name + ".tga").c_str());
}

TextureResource::~TextureResource() {
	delete _texture;
}

Texture* TextureResource::texture() const {
	return _texture;
}

void TextureResource::save(std::ofstream &file) const {
	util::writeString(file, name);
}