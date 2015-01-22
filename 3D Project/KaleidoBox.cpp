#include "KaleidoBox.h"

KaleidoBox::KaleidoBox() {
	// Vertices
	vertexNr = 6;
	vertexData = new Vertex[vertexNr];

	vertexData[0] = {
		0.5f, 0.5f, 0.0f,
		1.0f, 0.0f
	};
	vertexData[1] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 1.0f
	};
	vertexData[2] = {
		0.5f, -0.5f, 0.0f,
		1.0f, 1.0f
	};
	vertexData[3] = {
		-0.5f, 0.5f, 0.0f,
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

KaleidoBox::~KaleidoBox() {
	delete[] vertexData;
	delete[] indexData;
}

Geometry::Vertex* KaleidoBox::vertices() const {
	return vertexData;
}

unsigned short KaleidoBox::vertexCount() const {
	return vertexNr;
}

unsigned short* KaleidoBox::indices() const {
	return indexData;
}

unsigned int KaleidoBox::indexCount() const {
	return indexNr;
}