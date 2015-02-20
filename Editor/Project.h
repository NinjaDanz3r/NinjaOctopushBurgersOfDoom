#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <string>
#include "Resources.h"

/// A game project.
class Project {
	public:
		/// Constructor.
		Project();

		/// Destructor.
		~Project();
	
		/// Filename of project file.
		std::string filename;

		/// Save project to file.
		void save();

		/// Load project from file.
		void load();

		/// Get resources.
		/**
		 * @return The project's resources.
		 */
		Resources* resources() const;

	private:
		Resources* _resources;
};

#endif