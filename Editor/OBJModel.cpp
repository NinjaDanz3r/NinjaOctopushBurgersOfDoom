#include "OBJModel.h"

OBJModel::OBJModel(const char* filename) {
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

glm::vec3 OBJModel::readVec3(std::ifstream &modelFile) {
	glm::vec3 vec;
	modelFile >> vec.x >> vec.y >> vec.z;
	return vec;
}

glm::vec2 OBJModel::readVec2(std::ifstream &modelFile) {
	glm::vec2 vec;
	modelFile >> vec.x >> vec.y;
	return vec;
}

Geometry::Vertex OBJModel::readVertex(std::ifstream &modelFile, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &textureCoordinates) {
	Vertex vertex;
	char delimiter;
	unsigned int index;

	// Position.
	modelFile >> index;
	vertex.position = positions[index - 1];

	// Texture coordinate.
	modelFile >> delimiter >> index;
	vertex.textureCoordinate = textureCoordinates[index - 1];
	// OpenGL has origin in lower left corner, not upper left corner.
	vertex.textureCoordinate.y = 1.f - vertex.textureCoordinate.y;

	// Normal.
	modelFile >> delimiter >> index;
	vertex.normal = glm::normalize(normals[index - 1]);

	return vertex;
}