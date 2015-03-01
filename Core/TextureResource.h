#ifndef __TEXTURERESOURCE_H__
#define __TEXTURERESOURCE_H__

#include "Core.h"
#include <string>
#include <fstream>
#include "Texture.h"

/// A texture resource.
class TextureResource {
	public:
		/// Create new texture resource.
		/**
		* @param name Name.
		* @param directory Directory to load from.
		*/
		CORE_EXPORT TextureResource(const std::string &name, std::string directory);

		/// Create new texture resource.
		/**
		* @param file File stream to load from.
		* @param directory Directory to load from.
		*/
		CORE_EXPORT TextureResource(std::ifstream &file, std::string directory);

		/// Destructor.
		CORE_EXPORT ~TextureResource();

		/// Name of the texture resource.
		std::string name;

		/// Get texture.
		/**
		 * @return The texture.
		 */
		CORE_EXPORT Texture* texture() const;

		/// Save model resource to file.
		/**
		* @param file File stream to save to.
		*/
		CORE_EXPORT void save(std::ofstream &file) const;

	private:
		Texture* _texture;
};

#endif