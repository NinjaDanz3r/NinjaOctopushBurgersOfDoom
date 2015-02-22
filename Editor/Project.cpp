#include "Project.h"
#include <fstream>

Project::Project() {
	_resources = new Resources();
}

Project::~Project() {
	delete _resources;
}

std::string Project::filename() const {
	return _filename;
}

void Project::setFilename(std::string filename) {
	_filename = filename;
	directory = filename.substr(0, filename.rfind('/'));
}

void Project::save() {
	std::ofstream file;
	file.open(_filename.c_str(), std::ios_base::binary);

	_resources->save(file, directory);

	file.close();
}

void Project::load() {
	std::ifstream file;
	file.open(_filename.c_str(), std::ios_base::binary);

	_resources->load(file, directory);

	file.close();
}

Resources* Project::resources() const {
	return _resources;
}