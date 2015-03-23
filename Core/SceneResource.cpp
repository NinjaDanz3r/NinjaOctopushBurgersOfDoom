#include "SceneResource.h"
#include "util.h"

SceneResource::SceneResource(const std::string &name) {
	this->name = name;
}

SceneResource::SceneResource(std::ifstream &file, std::string directory) {
	name = util::readString(file);
	file.read(reinterpret_cast<char*>(&playerPosition), sizeof(playerPosition));
}

SceneResource::~SceneResource() {
	
}

void SceneResource::save(std::ofstream &file, std::string directory) const {
	util::writeString(file, name);
	file.write(reinterpret_cast<const char*>(&playerPosition), sizeof(playerPosition));
}