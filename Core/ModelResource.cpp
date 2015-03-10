#include "ModelResource.h"
#include "util.h"

ModelResource::ModelResource(const std::string &name, Model* model) {
	this->name = name;
	_model = model;
}

ModelResource::ModelResource(std::ifstream &file, std::string directory) {
	name = util::readString(file);
	_model = new Model((directory + '/' + name + ".bin").c_str());
}

ModelResource::~ModelResource() {
	delete _model;
}

Model* ModelResource::model() const {
	return _model;
}

void ModelResource::save(std::ofstream &file, std::string directory) const {
	util::writeString(file, name);
	_model->save((directory + '/' + name + ".bin").c_str());
}