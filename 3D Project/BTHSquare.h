#ifndef __BTHSQUARE_H__
#define __BTHSQUARE_H__

// Represents a BTH square.
class BTHSquare {
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
		BTHSquare();

		// Destructor
		~BTHSquare();

		// Gets all the triangle vertexes.
		TriangleVertex* vertexes() const;

		// Gets the number of vertexes.
		int count() const;
	private:
		TriangleVertex *data = nullptr;
		int dataNr = 0;
};

#endif