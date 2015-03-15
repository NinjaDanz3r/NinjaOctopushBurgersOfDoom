#ifndef __DATASTRUCTURES_H__
#define __DATASTRUCTURES_H__
#include "GeometryObject.h"
#include <vector>
#include <glm/glm.hpp>
#include "Rectangle2D.h"
#include <Frustum.h>
#include <map>

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
		QuadTree(const Rectangle2D & _rect, int _depth, int _maxDepth);
		~QuadTree();
		bool addObject(GeometryObject* object, Rectangle2D rect); //returns true if object was added.
		void getObjects(Frustum & frustum, std::map<GeometryObject*, GeometryObject*>& GeometryMap);
		void debugTree(std::string test);
	private:

		//glm::vec2 origin; //X, Y worldpos origin.
		//glm::vec2 dimensions;
		//float width; //Width of cubes
		//float height; //"Height" of cubes
		Rectangle2D rectangle;

		QuadTree* childTree[4];
		
		unsigned int depth;
		unsigned int maxDepth;

		std::vector < GeometryObject* > objects;
		bool isLeaf;
};


#endif