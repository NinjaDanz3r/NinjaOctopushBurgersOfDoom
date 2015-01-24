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

	// Convert height map to float.
	heightMap = new float*[width];
	for (int i = 0; i < width; i++) {
		heightMap[i] = new float[height];
	}

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			heightMap[x][y] = data[(x + y*width)*components] / 256.f;
		}
	}

	stbi_image_free(data);

	generateVertices();
	generateIndices();
}

Terrain::~Terrain() {
	delete[] vertexData;
	delete[] indexData;
	
	for (int i = 0; i < width; i++) {
		delete[] heightMap[i];
	}
	delete[] heightMap;
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

void Terrain::generateVertices() {
	vertexNr = width * height;
	vertexData = new Vertex[vertexNr];

	for (unsigned int i = 0; i < vertexNr; i++) {
		vertexData[i] = {
			static_cast<float>(i % width) / width - 0.5f,
			heightMap[i % width][i / width],
			static_cast<float>(i / width) / height - 0.5f,
			static_cast<float>(i % width) / width,
			static_cast<float>(i / width) / height
		};
	}
}

void Terrain::generateIndices() {
	indexNr = (width - 1) * (height - 1) * 6;
	indexData = new unsigned int[indexNr];

	for (unsigned int i = 0; i < indexNr; i += 6) {
		unsigned int x = (i / 6) % (width - 1);
		unsigned int y = (i / 6) / (width - 1);

		indexData[i] = x + y*width;
		indexData[i + 1] = (x + 1) + (y + 1)*width;
		indexData[i + 2] = (x + 1) + y*width;
		indexData[i + 3] = x + y*width;
		indexData[i + 4] = x + (y + 1)*width;
		indexData[i + 5] = (x + 1) + (y + 1)*width;
	}
}