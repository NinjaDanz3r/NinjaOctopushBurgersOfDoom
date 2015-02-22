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

		/// Get filename of project file.
		/**
		 * @return The filename.
		 */
		std::string filename() const;

		/// Set filename of project file.
		/**
		 * @param filename Filename.
		 */
		void setFilename(std::string filename);

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
		std::string _filename;
		std::string directory;
};

#endif