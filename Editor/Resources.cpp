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
	file << models->size();
	for (auto model : *models) {
		model->save(file);
	}
}

void Resources::load(std::ifstream &file) {
	std::vector<ModelResource*>::size_type size;
	file >> size;

	for (auto i = 0; i < size; i++) {
		models->push_back(new ModelResource(file));
	}
}

std::vector<ModelResource*>* Resources::modelResources() const {
	return models;
}