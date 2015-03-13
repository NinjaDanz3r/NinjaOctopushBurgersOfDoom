#ifndef __DATASTRUCTURES_H__
#define __DATASTRUCTURES_H__
#include "GeometryObject.h"
#include <vector>
#include <glm/glm.hpp>

class QuadTree;

//Enum to make spatial relations more intuitive.
enum Directions
{
	Q1 = 0, //First quadrant, northwest
	Q2,		//Second quadrant, northeast
	Q3,		//Third quadrant, southeast
	Q4		//Fourth quadrant, southwest
};

class QuadTree
{
	public:
		QuadTree(glm::vec2 _origin, float _dim, int _depth, int _maxDepth);
		~QuadTree();
		bool addObject(GeometryObject* object); //returns true if object was added.
		bool containsObject(GeometryObject* object);
		void debugTree(std::string test);
	private:
		glm::vec2 origin; //X, Y worldpos origin.
		float width; //Width of cubes
		std::vector < GeometryObject* > objects;
		QuadTree* childTree[4];
		unsigned int depth;
		unsigned int maxDepth;
		bool isLeaf;
};


#endif