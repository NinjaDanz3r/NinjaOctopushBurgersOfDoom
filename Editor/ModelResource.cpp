#include "ModelResource.h"
#include "OBJModel.h"
#include <util.h>

ModelResource::ModelResource(const std::string &name, const std::string &filename) {
	this->name = name;
	model = new OBJModel(filename.c_str());
}

ModelResource::ModelResource(std::ifstream &file, std::string directory) {
	name = util::readString(file);
	model = new Model((directory + '/' + name + ".bin").c_str());
}

ModelResource::~ModelResource() {
	delete model;
}

void ModelResource::save(std::ofstream &file, std::string directory) const {
	util::writeString(file, name);
	model->save((directory + '/' + name + ".bin").c_str());
}