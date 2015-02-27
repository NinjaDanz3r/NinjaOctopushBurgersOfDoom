#include "Resources.h"
#include "util.h"

Resources::Resources() {
	models = new std::vector<ModelResource*>();
}

Resources::~Resources() {
	for (auto model : *models) {
		delete model;
	}
	delete models;
}

void Resources::save(std::ofstream &file, std::string directory) {
	// Models
	util::createDirectory((directory + '/' + "Models").c_str());

	std::vector<ModelResource*>::size_type size = models->size();
	file.write(reinterpret_cast<const char*>(&size), sizeof(size));

	for (auto model : *models) {
		model->save(file, directory + '/' + "Models");
	}
}

void Resources::load(std::ifstream &file, std::string directory) {
	std::vector<ModelResource*>::size_type size;
	file.read(reinterpret_cast<char*>(&size), sizeof(size));

	for (auto i = 0; i < size; i++) {
		models->push_back(new ModelResource(file, directory));
	}
}

std::vector<ModelResource*>* Resources::modelResources() const {
	return models;
}