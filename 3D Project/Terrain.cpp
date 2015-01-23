#include "Terrain.h"

Terrain::Terrain() {
	// Vertices
	vertexNr = 4;
	vertexData = new Vertex[vertexNr];

	vertexData[0] = {
		0.5f, 0.0f, -0.5f,
		1.0f, 0.0f
	};
	vertexData[1] = {
		-0.5f, 0.0f, 0.5f,
		0.0f, 1.0f
	};
	vertexData[2] = {
		0.5f, 0.0f, 0.5f,
		1.0f, 1.0f
	};
	vertexData[3] = {
		-0.5f, 0.0f, -0.5f,
		0.0f, 0.0f
	};

	// Vertexindices
	indexNr = 6;
	indexData = new unsigned short[indexNr];

	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;
	indexData[3] = 0;
	indexData[4] = 3;
	indexData[5] = 1;
}

Terrain::~Terrain() {
	delete[] vertexData;
	delete[] indexData;
}

Geometry::Vertex* Terrain::vertices() const {
	return vertexData;
}

unsigned short Terrain::vertexCount() const {
	return vertexNr;
}

unsigned short* Terrain::indices() const {
	return indexData;
}

unsigned int Terrain::indexCount() const {
	return indexNr;
}