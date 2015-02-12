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
	normals = new glm::vec3*[width];
	for (int i = 0; i < width; i++) {
		heightMap[i] = new float[height];
		normals[i] = new glm::vec3[height];
	}

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			heightMap[x][y] = data[(x + y*width)*components] / 256.f;
		}
	}

	stbi_image_free(data);

	filter3x3();
	calculateNormals();

	generateVertices();
	generateIndices();

	for (int i = 0; i < width; i++) {
		delete[] normals[i];
	}
	delete[] normals;
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

float Terrain::getY(float x, float z) const {
	float xInTerrain = ((x - position().x) / scale().x + 0.5f) * width;
	float zInTerrain = ((z - position().z) / scale().z + 0.5f) * height;

	if (xInTerrain < 0.f || xInTerrain >= width - 1 || zInTerrain < 0.f || zInTerrain >= height - 1) {
		return 0.f;
	}

	int xFloor = (int) xInTerrain;
	int zFloor = (int)zInTerrain;

	float dx = xInTerrain - xFloor;
	float dz = zInTerrain - zFloor;

	// Bilinear interpolation.
	float height = (1.f - dx)*(1.f - dz) * heightMap[xFloor][zFloor] +
		           dx * (1.f - dz) * heightMap[xFloor + 1][zFloor] +
		           (1.f - dx) * dz * heightMap[xFloor][zFloor + 1] +
		           dx * dz * heightMap[xFloor + 1][zFloor + 1];

	return height * scale().y + position().y;
}

void Terrain::generateVertices() {
	vertexNr = width * height;
	vertexData = new Vertex[vertexNr];

	for (unsigned int i = 0; i < vertexNr; i++) {
		vertexData[i] = {
			// Position
			static_cast<float>(i % width) / width - 0.5f,
			heightMap[i % width][i / width],
			static_cast<float>(i / width) / height - 0.5f,
			// Normal
			normals[i % width][i / width].x,
			normals[i % width][i / width].y,
			normals[i % width][i / width].z,
			// Texture coordinates
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

void Terrain::filter3x3() {
	float** filteredHeightMap = new float*[width];
	for (int i = 0; i < width; i++) {
		filteredHeightMap[i] = new float[height];
	}

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			filteredHeightMap[x][y] = sampleHeight(x, y);
		}
	}

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			heightMap[x][y] = filteredHeightMap[x][y];
		}
	}

	for (int i = 0; i < width; i++) {
		delete[] filteredHeightMap[i];
	}
	delete[] filteredHeightMap;
}

float Terrain::sampleHeight(int x, int y) const {
	int num = 0;
	float sum = 0.f;

	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y; j++) {
			if (i >= 0 && i < width && j >= 0 && j < height) {
				num++;
				sum += heightMap[i][j];
			}
		}
	}

	return sum / num;
}

void Terrain::calculateNormals() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			float sx = heightMap[x < width - 1 ? x + 1 : x][y] - heightMap[x > 0 ? x - 1 : x][y];
			if (x == 0 || x == width - 1)
				sx *= 2.f;

			float sy = heightMap[x][y<height - 1 ? y + 1 : y] - heightMap[x][y > 0 ? y - 1 : y];
			if (y == 0 || y == height - 1)
				sy *= 2.f;

			normals[x][y] = glm::normalize(glm::vec3(-width * sx, 2.f, -height * sy));
		}
	}
}