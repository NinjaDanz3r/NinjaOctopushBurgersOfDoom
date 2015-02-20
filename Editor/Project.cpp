#include "Project.h"
#include <fstream>

void Project::save() {
	std::ofstream file;
	file.open(filename.c_str());
	file.close();
}

void Project::load() {
	
}