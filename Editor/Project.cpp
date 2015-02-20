#include "Project.h"
#include <fstream>

Project::Project() {
	_resources = new Resources();
}

Project::~Project() {
	delete _resources;
}

void Project::save() {
	std::ofstream file;
	file.open(filename.c_str(), std::ios_base::binary);

	_resources->save(file);

	file.close();
}

void Project::load() {
	std::ifstream file;
	file.open(filename.c_str(), std::ios_base::binary);

	_resources->load(file);

	file.close();
}

Resources* Project::resources() const {
	return _resources;
}