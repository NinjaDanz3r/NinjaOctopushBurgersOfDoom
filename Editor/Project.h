#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <string>

/// A game project.
class Project {
public:
	/// Filename of project file.
	std::string filename;

	/// Save project to file.
	void save();

	/// Load project from file.
	void load();
};

#endif