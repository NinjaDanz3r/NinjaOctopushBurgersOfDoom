#include "Resources.h"

Resources::Resources() {
	models = new std::vector<ModelResource*>();
}

Resources::~Resources() {
	for (auto model : *models) {
		delete model;
	}
	delete models;
}

void Resources::save(std::ofstream &file) {
	std::vector<ModelResource*>::size_type size = models->size();
	file.write(reinterpret_cast<const char*>(&size), sizeof(size));

	for (auto model : *models) {
		model->save(file);
	}
}

void Resources::load(std::ifstream &file) {
	std::vector<ModelResource*>::size_type size;
	file.read(reinterpret_cast<char*>(&size), sizeof(size));

	for (auto i = 0; i < size; i++) {
		models->push_back(new ModelResource(file));
	}
}

std::vector<ModelResource*>* Resources::modelResources() const {
	return models;
}