#include "ModelResource.h"
#include "OBJModel.h"
#include "util.h"

ModelResource::ModelResource(const std::string &name, const std::string &filename) {
	this->name = name;
	this->filename = filename;

	model = new OBJModel(filename.c_str());
	this->filename.append(".bin");
}

ModelResource::ModelResource(std::ifstream &file) {
	name = util::readString(file);
	filename = util::readString(file);

	model = new Model(filename.c_str());
}

ModelResource::~ModelResource() {
	delete model;
}

void ModelResource::save(std::ofstream &file) const {
	util::writeString(file, name);
	util::writeString(file, filename);
	model->save(filename.c_str());
}