#ifndef __DATASTRUCTURES_H__
#define __DATASTRUCTURES_H__
#include "GeometryObject.h"
#include <vector>

class QuadTree
{
	public:
		void createQuadTree(int depth);
		QuadTree();
	private:
		QuadNode* root;
		unsigned int numNodes;
		unsigned int depth;
};

class QuadNode
{
	public:
		QuadNode* childNodes[4];
		std::vector<GeometryObject> geometryList;
};

#endif