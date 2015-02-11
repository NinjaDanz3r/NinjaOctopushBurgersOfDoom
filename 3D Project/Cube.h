#ifndef _CUBE_H_
#define _CUBE_H_
#include "Object.h"
class Cube :public Object
{
	public:
		// Represents a vertex point in a triangle.
		struct TriangleVertex
		{
			// Position.
			float x, y, z;
			// Texture coordinates.
			float u, v;
		};

		// Create triangle data.
		Cube();

		// Destructor
		~Cube();

		// Gets all the triangle vertexes.
		TriangleVertex* vertexes() const;

		// Gets the number of vertexes.
		int count() const;
	private:
		TriangleVertex *data = nullptr;
		int dataNr = 0;
};
#endif

