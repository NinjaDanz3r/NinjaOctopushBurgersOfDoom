#include "Resources.h"
#include "util.h"

Resources::Resources() {
	models = new std::vector<ModelResource*>();
	textures = new std::map<std::string, TextureResource*>();
}

Resources::~Resources() {
	for (auto model : *models) {
		delete model;
	}
	delete models;

	for (auto texture : *textures) {
		delete texture.second;
	}
	delete textures;
}

void Resources::save(std::ofstream &file, std::string directory) {
	// Textures
	util::createDirectory((directory + '/' + "Textures").c_str());

	std::vector<TextureResource*>::size_type texturesSize = textures->size();
	file.write(reinterpret_cast<const char*>(&texturesSize), sizeof(texturesSize));

	for (auto texture : *textures) {
		texture.second->save(file);
	}
	
	// Models
	util::createDirectory((directory + '/' + "Models").c_str());

	std::vector<ModelResource*>::size_type modelsSize = models->size();
	file.write(reinterpret_cast<const char*>(&modelsSize), sizeof(modelsSize));

	for (auto model : *models) {
		model->save(file, directory + '/' + "Models");
	}
}

void Resources::load(std::ifstream &file, std::string directory) {
	// Textures
	std::vector<TextureResource*>::size_type texturesSize;
	file.read(reinterpret_cast<char*>(&texturesSize), sizeof(texturesSize));

	for (auto i = 0; i < texturesSize; i++) {
		TextureResource* texture = new TextureResource(file, directory);
		(*textures)[texture->name] = texture;
	}

	// Models
	std::vector<ModelResource*>::size_type modelsSize;
	file.read(reinterpret_cast<char*>(&modelsSize), sizeof(modelsSize));

	for (auto i = 0; i < modelsSize; i++) {
		models->push_back(new ModelResource(file, directory));
	}
}

std::vector<ModelResource*>* Resources::modelResources() const {
	return models;
}

std::map<std::string, TextureResource*>* Resources::textureResources() const {
	return textures;
}