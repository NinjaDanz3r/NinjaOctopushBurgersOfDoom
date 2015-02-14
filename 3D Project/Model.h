#ifndef __MODEL_H__
#define __MODEL_H__

#include "Geometry.h"

/// A model loaded from an OBJ file.
class Model : public Geometry {
public:
	/// Create new model at origo.
	/**
	 * @param filename Filename (relative or absolute) to the OBJ model file.
	 */
	Model(const char* filename);

	/// Destructor
	~Model();

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

private:
	Vertex *vertexData = nullptr;
	unsigned int vertexNr = 0;

	unsigned int* indexData = nullptr;
	unsigned int indexNr = 0;
};

#endif