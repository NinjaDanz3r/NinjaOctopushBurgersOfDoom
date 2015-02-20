#ifndef __MODELRESOURCE_H__
#define __MODELRESOURCE_H__

#include <string>
#include <fstream>

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
		 */
		ModelResource(std::ifstream &file);

		/// Destructor.
		~ModelResource();

		/// Name of the model resource.
		std::string name;

		/// Filename of model file.
		std::string filename;

		/// Save model resource to file.
		/**
		 * @param file File stream to save to.
		 */
		void save(std::ofstream &file) const;
};

#endif