#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Geometry.h"

/// A square.
class Square : public Geometry {
	public:
		/// Create new square at origo.
		Square();

		/// Destructor
		~Square();

		/// Get all the vertices.
		/**
		* @return Array of vertices
		*/
		virtual Vertex* vertices() const = 0;

		/// Get the number of vertices.
		/**
		* @return The number of vertices
		*/
		virtual unsigned int vertexCount() const = 0;

		/// Get all the vertex indices.
		/**
		* @return Array of vertex indices
		*/
		virtual unsigned int* indices() const = 0;

		/// Get the number of indicies.
		/**
		* @return The number of vertex indices.
		*/
		virtual unsigned int indexCount() const = 0;

	private:
		Vertex *vertexData = nullptr;
		unsigned int vertexNr = 0;

		unsigned int* indexData = nullptr;
		unsigned int indexNr = 0;
};

#endif