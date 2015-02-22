#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <fstream>
#include <vector>
#include "ModelResource.h"

/// Contains the project's resources (models, etc.).
class Resources {
	public:
		/// Constructor.
		Resources();
		
		/// Destructor.
		~Resources();

		/// Save resources to file stream.
		/**
		 * @param file File stream to save to.
		 * @param directory Directory to save to.
		 */
		void save(std::ofstream &file, std::string directory);

		/// Load from file stream.
		/**
		 * @param file File stream to load from.
		 * @param directory  Directory to load from.
		 */
		void load(std::ifstream &file, std::string directory);

		/// Get model resources.
		/**
		 * @return Model resources.
		 */
		std::vector<ModelResource*>* modelResources() const;

	private:
		std::vector<ModelResource*>* models;
};

#endif