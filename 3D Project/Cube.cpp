#include "Cube.h"

<<<<<<< HEAD

Cube::Cube()
{
	dataNr = 36;
	data = new TriangleVertex[dataNr];
	
	//FRONT	
	data[0] = { 1.0f, 1.0f, 1.0f, 1.0f, 0.0f };
	data[1] = { -1.0f, 1.0f, 1.0f, 0.0f, 0.0f };
	data[2] = { 1.0f, -1.0f, 1.0f,1.0f, 1.0f };
	
	data[3] = { -1.0f, 1.0f, 1.0f, 0.0f, 0.0f };
	data[4] = { -1.0f, -1.0f, 1.0f, 0.0f, 1.0f };
	data[5] = { 1.0f, -1.0f, 1.0f, 1.0f, 1.0f };

	//BACK
	data[6] = { 1.0f, 1.0f, -1.0f, 0.0f, 0.0f };
	data[7] = { -1.0f, -1.0f, -1.0f, 1.0f, 1.0f };
	data[8] = { -1.0f, 1.0f, -1.0f, 1.0f, 0.0f };

	data[9] = { 1.0f, 1.0f, -1.0f, 0.0f, 0.0f };
	data[10] = { 1.0f, -1.0f, -1.0f, 0.0f, 1.0f };
	data[11] = { -1.0f, -1.0f, -1.0f, 1.0f, 1.0f };

	//BOTTOM
	data[12] = { 1.0f, -1.0f, 1.0f, 0.0f, 0.0f };
	data[13] = { -1.0f, -1.0f, 1.0f, 1.0f, 0.0f };
	data[14] = { -1.0f, -1.0f, -1.0f, 1.0f, 1.0f };
	
	data[15] = { 1.0f, -1.0f, 1.0f, 0.0f, 0.0f };
	data[16] = { -1.0f, -1.0f, -1.0f, 1.0f, 1.0f };
	data[17] = { 1.0f, -1.0f, -1.0f, 0.0f, 1.0f };

	//TOP
	data[18] = { 1.0f, 1.0f, 1.0f, 0.0f, 0.0f };
	data[19] = { -1.0f, 1.0f, -1.0f, 1.0f, 1.0f };
	data[20] = { -1.0f, 1.0f, 1.0f, 0.0f, 1.0f };
	
	data[21] = { 1.0f, 1.0f, 1.0f, 0.0f, 0.0f };
	data[22] = { 1.0f, 1.0f, -1.0f, 1.0f, 0.0f };
	data[23] = { -1.0f, 1.0f, -1.0f, 1.0f, 1.0f };
	
	//LEFT
	data[24] = { -1.0f, -1.0f, -1.0f, 0.0f, 1.0f };
	data[25] = { -1.0f, 1.0f, 1.0f, 1.0f, 0.0f };
	data[26] = { -1.0f, 1.0f, -1.0f, 0.0f, 0.0f };
	
	data[27] = { -1.0f, -1.0f, -1.0f, 0.0f, 1.0f }; 
	data[28] = { -1.0f, -1.0f, 1.0f, 1.0f, 1.0f };
	data[29] = { -1.0f, 1.0f, 1.0f, 1.0f, 0.0f };
	
	//RIGHT
	data[30] = { 1.0f, 1.0f, 1.0f, 0.0f, 0.0f };
	data[31] = { 1.0f, -1.0f, -1.0f, 1.0f, 1.0f };
	data[32] = { 1.0f, 1.0f, -1.0f, 1.0f, 0.0f };
	
	data[33] = { 1.0f, -1.0f, -1.0f, 1.0f, 1.0f };
	data[34] = { 1.0f, 1.0f, 1.0f, 0.0f, 0.0f };
	data[35] = { 1.0f, -1.0f, 1.0f, 0.0f, 1.0f };
	
}	


Cube::~Cube()
{
	delete[] data;
}

Cube::TriangleVertex* Cube::vertexes() const {
	return data;
}

int Cube::count() const {
	return dataNr;
}
=======
Cube::Cube() {
	// Vertices
	vertexNr = 24;
	vertexData = new Vertex[vertexNr];

	// Side 1
	vertexData[0] = {
		0.5f, 0.5f, 0.5f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f
	};
	vertexData[1] = {
		-0.5f, -0.5f, 0.5f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f
	};
	vertexData[2] = {
		0.5f, -0.5f, 0.5f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f
	};
	vertexData[3] = {
		-0.5f, 0.5f, 0.5f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f
	};

	// Side 2
	vertexData[4] = {
		-0.5f, 0.5f, -0.5f,
		-1.0f, 0.0f, 0.0f,
		0.0f, 0.0f
	};
	vertexData[5] = {
		-0.5f, -0.5f, -0.5f,
		-1.0f, 0.0f, 0.0f,
		0.0f, 1.0f
	};
	vertexData[6] = {
		-0.5f, -0.5f, 0.5f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 1.0f
	};
	vertexData[7] = {
		-0.5f, 0.5f, 0.5f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f
	};

	// Side 3
	vertexData[8] = {
		0.5f, 0.5f, -0.5f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f
	};
	vertexData[9] = {
		0.5f, -0.5f, -0.5f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f
	};
	vertexData[10] = {
		0.5f, -0.5f, 0.5f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f
	};
	vertexData[11] = {
		0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f
	};

	// Side 4
	vertexData[12] = {
		0.5f, 0.5f, -0.5f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f
	};
	vertexData[13] = {
		-0.5f, -0.5f, -0.5f,
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f
	};
	vertexData[14] = {
		0.5f, -0.5f, -0.5f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f
	};
	vertexData[15] = {
		-0.5f, 0.5f, -0.5f,
		0.0f, 0.0f, -1.0f,
		1.0f, 1.0f
	};

	// Side 5
	vertexData[16] = {
		-0.5f, -0.5f, 0.5f,
		0.0f, -1.0f, 0.0f,
		0.0f, 0.0f
	};
	vertexData[17] = {
		0.5f, -0.5f, 0.5f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f
	};
	vertexData[18] = {
		0.5f, -0.5f, -0.5f,
		0.0f, -1.0f, 0.0f,
		1.0f, 1.0f
	};
	vertexData[19] = {
		-0.5f, -0.5f, -0.5f,
		0.0f, -1.0f, 0.0f,
		0.0f, 1.0f
	};

	// Side 6
	vertexData[20] = {
		-0.5f, 0.5f, 0.5f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f
	};
	vertexData[21] = {
		0.5f, 0.5f, 0.5f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f
	};
	vertexData[22] = {
		0.5f, 0.5f, -0.5f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f
	};
	vertexData[23] = {
		-0.5f, 0.5f, -0.5f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f
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
	indexData[6] = 4;
	indexData[7] = 6;
	indexData[8] = 7;
	indexData[9] = 4;
	indexData[10] = 5;
	indexData[11] = 6;

	// Side 3
	indexData[12] = 11;
	indexData[13] = 9;
	indexData[14] = 8;
	indexData[15] = 11;
	indexData[16] = 10;
	indexData[17] = 9;

	// Side 4
	indexData[18] = 12;
	indexData[19] = 13;
	indexData[20] = 15;
	indexData[21] = 12;
	indexData[22] = 14;
	indexData[23] = 13;

	// Side 5
	indexData[24] = 16;
	indexData[25] = 19;
	indexData[26] = 18;
	indexData[27] = 16;
	indexData[28] = 18;
	indexData[29] = 17;

	// Side 6
	indexData[30] = 20;
	indexData[31] = 22;
	indexData[32] = 23;
	indexData[33] = 20;
	indexData[34] = 21;
	indexData[35] = 22;
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
>>>>>>> origin/master
