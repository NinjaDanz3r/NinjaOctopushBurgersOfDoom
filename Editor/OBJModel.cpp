#include "Model.h"
#include <limits>
#include "util.h"
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
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec2> textureCoordinates;
	std::vector<Face> faces;

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
				tangents.push_back(glm::vec3(0.f, 0.f, 0.f));
				break;
			case 'n':
				// Normal
				normals.push_back(glm::normalize(readVec3(modelFile)));
				break;
			case 't':
				// Texture coordinate
				textureCoordinates.push_back(readVec2(modelFile));
				break;
			}
			break;
		case 'f':
			// Face
			faces.push_back(readFace(modelFile));
			break;
		default:
			modelFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	modelFile.close();

	calculateTangents(faces, positions, textureCoordinates, tangents);

	for (const Face& face : faces) {
		for (int i = 0; i < 3; i++) {
			Vertex vertex;

			vertex.position = positions[face.vertices[i].positionIndex];
			vertex.textureCoordinate = textureCoordinates[face.vertices[i].textureIndex];

			// OpenGL has origin in lower left corner, not upper left corner.
			vertex.textureCoordinate.y = 1.f - vertex.textureCoordinate.y;

			vertex.normal = normals[face.vertices[i].normalIndex];
			vertex.tangent = tangents[face.vertices[i].positionIndex];

			vertices.push_back(vertex);
		}
	}

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

	generateBuffers();
	generateVertexArray();
}

glm::vec3 OBJModel::readVec3(std::ifstream& modelFile) {
	glm::vec3 vec;
	modelFile >> vec.x >> vec.y >> vec.z;
	return vec;
}

glm::vec2 OBJModel::readVec2(std::ifstream& modelFile) {
	glm::vec2 vec;
	modelFile >> vec.x >> vec.y;
	return vec;
}

OBJModel::Face OBJModel::readFace(std::ifstream& modelFile) {
	Face face;
	
	for (int i = 0; i < 3; i++)
		face.vertices[i] = readVertex(modelFile);

	return face;
}

OBJModel::Face::Vertex OBJModel::readVertex(std::ifstream& modelFile) {
	Face::Vertex vertex;
	char delimiter;
	unsigned int index;

	// Position.
	modelFile >> index;
	vertex.positionIndex = index - 1;

	// Texture coordinate.
	modelFile >> delimiter >> index;
	vertex.textureIndex = index - 1;

	// Normal.
	modelFile >> delimiter >> index;
	vertex.normalIndex = index - 1;

	return vertex;
}

void OBJModel::calculateTangents(std::vector<Face>& faces, std::vector<glm::vec3>& positions, std::vector<glm::vec2>& textureCoordinates, std::vector<glm::vec3>& tangents) {
	for (const Face& face : faces) {
		glm::vec3 edge1 = positions[face.vertices[1].positionIndex] - positions[face.vertices[0].positionIndex];
		glm::vec3 edge2 = positions[face.vertices[2].positionIndex] - positions[face.vertices[0].positionIndex];

		glm::vec2 deltaUV1 = textureCoordinates[face.vertices[1].textureIndex] - textureCoordinates[face.vertices[0].textureIndex];
		glm::vec2 deltaUV2 = textureCoordinates[face.vertices[2].textureIndex] - textureCoordinates[face.vertices[0].textureIndex];

		float f = 1.f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		glm::vec3 tangent = f * (deltaUV2.y * edge1 - deltaUV1.y * edge2);

		tangents[face.vertices[0].positionIndex] += tangent;
		tangents[face.vertices[1].positionIndex] += tangent;
		tangents[face.vertices[2].positionIndex] += tangent;
	}

	for (glm::vec3& tangent : tangents) {
		tangent = glm::normalize(tangent);
	}
}