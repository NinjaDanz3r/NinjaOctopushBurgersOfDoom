#ifndef __MODEL_H__
#define __MODEL_H__

#include <fstream>
#include <vector>
#include "Geometry.h"

/// A model loaded from our own binary model format.
class Model : public Geometry {
	public:
		/// Create new model at origo.
		/**
		 * @param filename Filename (relative or absolute) to the model file.
		 */
		Model(const char* filename);

		/// Destructor
		virtual ~Model();

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

		/// Save model to binary file.
		/**
		 * @param filename Filename (relative or absolute) to the model file.
		 */
		void save(const char* filename) const;

	protected:
		Model() { }

		Vertex *vertexData = nullptr;
		unsigned int vertexNr = 0;

		unsigned int* indexData = nullptr;
		unsigned int indexNr = 0;
};

#endif