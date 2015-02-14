#include "Model.h"
#include <limits>
#include "util.h"

Model::Model(const char* filename) {
	std::ifstream modelFile;
	modelFile.open(filename);
	if (!modelFile.is_open()) {
		fprintf(stderr, "Couldn't open model file %s for reading.\n", filename);
		fflush(stderr);
	}

	std::vector<Vertex> vertices;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoordinates;

	// Parse OBJ file.
	while (!modelFile.eof()) {
		char c, c2;
		modelFile >> c;
		switch (c) {
		case 'v':
			modelFile >> std::noskipws >> c2 >> std::skipws;
			switch (c2) {
			case ' ':
				// Position
				positions.push_back(readVec3(modelFile));
				break;
			case 'n':
				// Normal
				normals.push_back(readVec3(modelFile));
				break;
			case 't':
				// Texture coordinate
				textureCoordinates.push_back(readVec2(modelFile));
				break;
			}
			break;
		case 'f':
			// Face
			vertices.push_back(readVertex(modelFile, positions, normals, textureCoordinates));
			vertices.push_back(readVertex(modelFile, positions, normals, textureCoordinates));
			vertices.push_back(readVertex(modelFile, positions, normals, textureCoordinates));
			break;
		default:
			modelFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	modelFile.close();

	vertexNr = vertices.size();
	vertexData = new Vertex[vertexNr];
	for (unsigned int i = 0; i < vertexNr; i++) {
		vertexData[i] = vertices[i];
	}

	indexNr = vertexNr;
	indexData = new unsigned int[indexNr];
	for (unsigned int i = 0; i < indexNr; i++) {
		indexData[i] = i;
	}
}

Model::~Model() {
	delete[] vertexData;
	delete[] indexData;
}

Geometry::Vertex* Model::vertices() const {
	return vertexData;
}

unsigned int Model::vertexCount() const {
	return vertexNr;
}

unsigned int* Model::indices() const {
	return indexData;
}

unsigned int Model::indexCount() const {
	return indexNr;
}

glm::vec3 Model::readVec3(std::ifstream &modelFile) {
	glm::vec3 position;
	modelFile >> position.x >> position.y >> position.z;
	return position;
}

glm::vec2 Model::readVec2(std::ifstream &modelFile) {
	glm::vec2 textureCoordinate;
	modelFile >> textureCoordinate.x >> textureCoordinate.y;
	return textureCoordinate;
}

Geometry::Vertex Model::readVertex(std::ifstream &modelFile, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &textureCoordinates) {
	Vertex vertex;
	char delimiter;
	unsigned int index;

	// Position.
	modelFile >> index;
	vertex.x = positions[index-1].x;
	vertex.y = positions[index-1].y;
	vertex.z = positions[index-1].z;

	// Texture coordinate.
	modelFile >> delimiter >> index;
	vertex.u = textureCoordinates[index - 1].x;
	vertex.v = 1.f-textureCoordinates[index - 1].y;

	// Normal.
	modelFile >> delimiter >> index;
	vertex.normalX = normals[index-1].x;
	vertex.normalY = normals[index-1].y;
	vertex.normalZ = normals[index-1].z;

	return vertex;
}