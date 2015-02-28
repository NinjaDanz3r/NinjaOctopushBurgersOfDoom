#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "Core.h"
#include <fstream>
#include <vector>
#include "ModelResource.h"
#include "TextureResource.h"

/// Contains the project's resources (models, etc.).
class Resources {
	public:
		/// Constructor.
		CORE_EXPORT Resources();

		/// Destructor.
		CORE_EXPORT ~Resources();

		/// Save resources to file stream.
		/**
		* @param file File stream to save to.
		* @param directory Directory to save to.
		*/
		CORE_EXPORT void save(std::ofstream &file, std::string directory);

		/// Load from file stream.
		/**
		* @param file File stream to load from.
		* @param directory  Directory to load from.
		*/
		CORE_EXPORT void load(std::ifstream &file, std::string directory);

		/// Get model resources.
		/**
		* @return Model resources.
		*/
		CORE_EXPORT std::vector<ModelResource*>* modelResources() const;

		/// Get texture resources.
		/**
		* @return Texture resources
		*/
		CORE_EXPORT std::vector<TextureResource*>* textureResources() const;

	private:
		std::vector<ModelResource*>* models;
		std::vector<TextureResource*>* textures;
};

#endif