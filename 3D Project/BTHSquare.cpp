#include "BTHSquare.h"

BTHSquare::BTHSquare() {
	dataNr = 6;
	data = new TriangleVertex[dataNr];

	// First triangle
	data[0] = {
		0.5f, 0.5f, 0.0f,
		1.0f, 0.0f
	};
	data[1] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 1.0f
	};
	data[2] = {
		0.5f, -0.5f, 0.0f,
		1.0f, 1.0f
	};
	// Second triangle
	data[3] = {
		0.5f, 0.5f, 0.0f,
		1.0f, 0.0f
	};
	data[4] = {
		-0.5f, 0.5f, 0.0f,
		0.0f, 0.0f
	};
	data[5] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 1.0f
	};
}

BTHSquare::~BTHSquare() {
	delete[] data;
}

BTHSquare::TriangleVertex* BTHSquare::vertexes() const {
	return data;
}

int BTHSquare::count() const {
	return dataNr;
}