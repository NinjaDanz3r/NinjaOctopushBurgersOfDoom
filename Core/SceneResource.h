#ifndef __SCENERESOURCE_H__
#define __SCENERESOURCE_H__

#include "Core.h"
#include <string>
#include <fstream>

/** @ingroup core
 * @{
 */

/// A scene resource.
class SceneResource {
	public:
		/// Create new scene resource.
		/**
		 * @param name Name.
		 */
		CORE_EXPORT SceneResource(const std::string &name);

		/// Create new scene resource.
		/**
		 * @param file File stream to load from.
		 * @param directory Directory to load from.
		 */
		CORE_EXPORT SceneResource(std::ifstream &file, std::string directory);

		/// Destructor.
		CORE_EXPORT ~SceneResource();

		/// Name of the scene resource.
		std::string name;

		/// Save scene resource to file.
		/**
		 * @param file File stream to save to.
		 * @param directory Directory to save to.
		 */
		CORE_EXPORT void save(std::ofstream &file, std::string directory) const;

	private:
	
};

/** @} */

#endif