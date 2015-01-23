#include "Terrain.h"
#include <stb_image.h>
#include "util.h"

Terrain::Terrain(const char* filename) {
	// Load height map from file
	int components;
	unsigned char* data;
	data = stbi_load(filename, &width, &height, &components, 0);

	if (data == NULL) {
		fputs("Couldn't load image: ", stderr);
		util::log(filename);
	}

	fprintf(stderr, "Height map size: %ix%i\n", width, height);

	// TODO: Convert height map data to float.

	stbi_image_free(data);

	// Generate terrain vertices.
	vertexNr = width * height;
	vertexData = new Vertex[vertexNr];

	for (unsigned int i = 0; i < vertexNr; i++) {
		vertexData[i] = {
			static_cast<float>(i % width)/width - 0.5f,
			0.0f,
			static_cast<float>(i / width) / height - 0.5f,
			static_cast<float>(i % width) / width,
			static_cast<float>(i / width) / height
		};
	}

	// TODO: Generate terrain indices.

	// Vertexindices
	indexNr = 6;
	indexData = new unsigned int[indexNr];

	indexData[0] = 0;
	indexData[1] = 65535;
	indexData[2] = 255;
	indexData[3] = 0;
	indexData[4] = 65280;
	indexData[5] = 65535;
}

Terrain::~Terrain() {
	delete[] vertexData;
	delete[] indexData;
}

Geometry::Vertex* Terrain::vertices() const {
	return vertexData;
}

unsigned int Terrain::vertexCount() const {
	return vertexNr;
}

unsigned int* Terrain::indices() const {
	return indexData;
}

unsigned int Terrain::indexCount() const {
	return indexNr;
}