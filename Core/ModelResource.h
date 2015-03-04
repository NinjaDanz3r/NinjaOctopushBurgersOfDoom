#ifndef __MODELRESOURCE_H__
#define __MODELRESOURCE_H__

#include "Core.h"
#include <string>
#include <fstream>
#include "Model.h"

/** @ingroup core
 * @{
 */

/// A model resource.
class ModelResource {
	public:
		/// Create new model resource.
		/**
		 * @param name Name.
		 * @param model The model.
		 */
		CORE_EXPORT ModelResource(const std::string &name, Model* model);

		/// Create new model resource.
		/**
		 * @param file File stream to load from.
		 * @param directory Directory to load from.
		 */
		CORE_EXPORT ModelResource(std::ifstream &file, std::string directory);

		/// Destructor.
		CORE_EXPORT ~ModelResource();

		/// Name of the model resource.
		std::string name;

		/// Save model resource to file.
		/**
		 * @param file File stream to save to.
		 * @param directory Directory to save to.
		 */
		CORE_EXPORT void save(std::ofstream &file, std::string directory) const;

	private:
		Model* model;
};

/** @} */

#endif