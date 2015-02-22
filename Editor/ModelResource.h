#ifndef __MODELRESOURCE_H__
#define __MODELRESOURCE_H__

#include <string>
#include <fstream>
#include "Model.h"

/// A model resource.
class ModelResource {
	public:
		/// Create new model resource.
		/**
		 * @param name Name.
		 * @param filename Filename.
		 */
		ModelResource(const std::string &name, const std::string &filename);

		/// Create new model resource.
		/**
		 * @param file File stream to load from.
		 * @param directory Directory to load from.
		 */
		ModelResource(std::ifstream &file, std::string directory);

		/// Destructor.
		~ModelResource();

		/// Name of the model resource.
		std::string name;

		/// Save model resource to file.
		/**
		 * @param file File stream to save to.
		 * @param directory Directory to save to.
		 */
		void save(std::ofstream &file, std::string directory) const;

	private:
		Model* model;
};

#endif