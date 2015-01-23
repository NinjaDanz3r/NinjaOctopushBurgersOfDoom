#include "Cube.h"

Cube::Cube() {
	// Vertices
	vertexNr = 8;
	vertexData = new Vertex[vertexNr];

	vertexData[0] = {
		0.5f, 0.5f, 0.5f,
		1.0f, 0.0f
	};
	vertexData[1] = {
		-0.5f, -0.5f, 0.5f,
		0.0f, 1.0f
	};
	vertexData[2] = {
		0.5f, -0.5f, 0.5f,
		1.0f, 1.0f
	};
	vertexData[3] = {
		-0.5f, 0.5f, 0.5f,
		0.0f, 0.0f
	};
	vertexData[4] = {
		0.5f, 0.5f, -0.5f,
		0.0f, 1.0f
	};
	vertexData[5] = {
		-0.5f, -0.5f, -0.5f,
		1.0f, 0.0f
	};
	vertexData[6] = {
		0.5f, -0.5f, -0.5f,
		0.0f, 0.0f
	};
	vertexData[7] = {
		-0.5f, 0.5f, -0.5f,
		1.0f, 1.0f
	};

	// Vertexindices
	indexNr = 36;
	indexData = new unsigned int[indexNr];

	// Side 1
	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;
	indexData[3] = 0;
	indexData[4] = 3;
	indexData[5] = 1;

	// Side 2
	indexData[6] = 3;
	indexData[7] = 4;
	indexData[8] = 7;
	indexData[9] = 3;
	indexData[10] = 0;
	indexData[11] = 4;

	// Side 3
	indexData[12] = 0;
	indexData[13] = 6;
	indexData[14] = 4;
	indexData[15] = 0;
	indexData[16] = 2;
	indexData[17] = 6;

	// Side 4
	indexData[18] = 4;
	indexData[19] = 5;
	indexData[20] = 7;
	indexData[21] = 4;
	indexData[22] = 6;
	indexData[23] = 5;

	// Side 5
	indexData[24] = 2;
	indexData[25] = 5;
	indexData[26] = 6;
	indexData[27] = 2;
	indexData[28] = 1;
	indexData[29] = 5;

	// Side 6
	indexData[30] = 7;
	indexData[31] = 1;
	indexData[32] = 3;
	indexData[33] = 7;
	indexData[34] = 5;
	indexData[35] = 1;
}

Cube::~Cube() {
	delete[] vertexData;
	delete[] indexData;
}

Geometry::Vertex* Cube::vertices() const {
	return vertexData;
}

unsigned int Cube::vertexCount() const {
	return vertexNr;
}

unsigned int* Cube::indices() const {
	return indexData;
}

unsigned int Cube::indexCount() const {
	return indexNr;
}