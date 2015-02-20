#include "ModelResource.h"
#include "util.h"

ModelResource::ModelResource(const std::string &name, const std::string &filename) {
	this->name = name;
	this->filename = filename;
}

ModelResource::ModelResource(std::ifstream &file) {
	name = util::readString(file);
	filename = util::readString(file);
}

ModelResource::~ModelResource() {

}

void ModelResource::save(std::ofstream &file) const {
	util::writeString(file, name);
	util::writeString(file, filename);
}