#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "Geometry.h"
#include <glm/glm.hpp>

/// A terrain object.
class Terrain : public Geometry {
public:
	/// Create new terrain from the given height map.
	/**
	 * @param filename Filename (relative or absolute) to height map texture.
	 */
	Terrain(const char* filename);

	/// Destructor
	~Terrain();

	/// Get all the vertices.
	/**
	* @return Array of vertices
	*/
	Vertex* vertices() const;

	/// Get the number of vertices.
	/**
	* @return The number of vertices
	*/
	unsigned int vertexCount() const;

	/// Get all the vertex indices.
	/**
	* @return Array of vertex indices
	*/
	unsigned int* indices() const;

	/// Get the number of indicies.
	/**
	* @return The number of vertex indices.
	*/
	unsigned int indexCount() const;

	/// Gets the height of the terrain at a given location.
	/**
	 * If the position is outside the terrain, 0.0 is returned.
	 * @param x X-position in the world.
	 * @param z Z-position in the world.
	 * @return Height of the terrain.
	 */
	float getY(float x, float z) const;

	/// Get how many times the texture should repeat.
	/**
	 * Default: (1.0, 1.0)
	 * @return How many times the texture should repeat
	 */
	glm::vec2 textureRepeat() const;

	/// Set how many times the texture should repeat.
	/**
	 * @param repeat How many times the texture should repeat.
	 */
	void setTextureRepeat(glm::vec2 repeat);

private:
	void generateVertices();
	void generateIndices();
	void filter3x3();
	float sampleHeight(int x, int y) const;
	void calculateNormals();

	Vertex *vertexData = nullptr;
	unsigned int vertexNr = 0;

	unsigned int* indexData = nullptr;
	unsigned int indexNr = 0;

	float** heightMap;
	glm::vec3** normals;
	int width;
	int height;

	glm::vec2 _textureRepeat;
};

#endif