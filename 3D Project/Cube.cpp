#include "Cube.h"


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
