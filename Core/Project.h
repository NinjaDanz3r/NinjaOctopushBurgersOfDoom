#ifndef __PROJECT_H__
#define __PROJECT_H__

#include "Core.h"
#include <string>
#include "Resources.h"

/// A game project.
class Project {
public:
	/// Constructor.
	CORE_EXPORT Project();

	/// Destructor.
	CORE_EXPORT ~Project();

	/// Get filename of project file.
	/**
	* @return The filename.
	*/
	CORE_EXPORT std::string filename() const;

	/// Set filename of project file.
	/**
	* @param filename Filename.
	*/
	CORE_EXPORT void setFilename(std::string filename);

	/// Save project to file.
	CORE_EXPORT void save();

	/// Load project from file.
	CORE_EXPORT void load();

	/// Get resources.
	/**
	* @return The project's resources.
	*/
	CORE_EXPORT Resources* resources() const;

private:
	Resources* _resources;
	std::string _filename;
	std::string directory;
};

#endif