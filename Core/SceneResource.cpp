#include "SceneResource.h"
#include "util.h"

SceneResource::SceneResource(const std::string &name) {
	this->name = name;
}

SceneResource::SceneResource(std::ifstream &file, std::string directory) {
	name = util::readString(file);
}

SceneResource::~SceneResource() {
	
}

void SceneResource::save(std::ofstream &file, std::string directory) const {
	util::writeString(file, name);
}