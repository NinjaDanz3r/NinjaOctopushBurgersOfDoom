#include "convert.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_ONLY_BMP
#define STBI_ONLY_TGA
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace convert {
	void convertImage(const char* inName, const char* outName) {
		int width, height, components;
		unsigned char* data = stbi_load(inName, &width, &height, &components, 0);

		stbi_write_tga(outName, width, height, components, data);

		stbi_image_free(data);
	}
}