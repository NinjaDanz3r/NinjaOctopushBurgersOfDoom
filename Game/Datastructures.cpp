#include "Datastructures.h"


QuadTree::QuadTree(glm::vec3 _origin, glm::vec2 _dim, int _depth, int _maxDepth) {
	origin = _origin;
	dim = _dim;
	depth = _depth;
	maxDepth = _maxDepth;
	isLeaf = false;

	//If we're at a leaf, we should populate it with objects 
	if (_depth == _maxDepth) {
		isLeaf = true;
		return;
	}

	//Precalculate some values
	float halfWidth = dim.x / 2.f;
	glm::vec2 newDim(halfWidth, dim.y);
	int nextDepth = depth+1;

	childTree[Q1] = new QuadTree(glm::vec3(origin.x - halfWidth, origin.y, origin.z + halfWidth), newDim, nextDepth, maxDepth);
	childTree[Q2] = new QuadTree(glm::vec3(origin.x + halfWidth, origin.y, origin.z + halfWidth), newDim, nextDepth, maxDepth);
	childTree[Q3] = new QuadTree(glm::vec3(origin.x + halfWidth, origin.y, origin.z - halfWidth), newDim, nextDepth, maxDepth);
	childTree[Q4] = new QuadTree(glm::vec3(origin.x - halfWidth, origin.y, origin.z - halfWidth), newDim, nextDepth, maxDepth);
}

//Prints debug information
void QuadTree::debugTree(std::string test)
{
	if (depth == maxDepth)
	{
		fprintf(stderr, "===I'm a leaf node!\n My Data: \n");
		fprintf(stderr, "Depth: %i\n maxDepth: %i\n Origin: %f,%f,%f\n Dimensions: Width %f Height %f\n\n", depth, maxDepth, origin.x, origin.y, origin.z, dim.x, dim.y);
		return;
	}
	else
	{
		fprintf(stderr, "===I'm a quadrant node!\n I live at: %s\n My Data: \n", test.c_str());
		fprintf(stderr, "Depth: %i\n maxDepth: %i\n Origin: %f,%f,%f\n Dimensions: Width %f Height %f\n\n", depth, maxDepth, origin.x, origin.y, origin.z, dim.x, dim.y);
		childTree[Q1]->debugTree("Q1");
		childTree[Q1]->debugTree("Q2");
		childTree[Q1]->debugTree("Q3");
		childTree[Q1]->debugTree("Q4");
	}
}

//Add object to leaf node. Returns true if object was found to be within cubes.
bool QuadTree::addObject(GeometryObject* object) {
	if (depth == maxDepth){
		objects.push_back(object);
		return true;
	}
	else
	{
		if (childTree[Q1]->containsObject(object))
			return childTree[Q1]->addObject(object);
		if (childTree[Q2]->containsObject(object))
			return childTree[Q2]->addObject(object);
		if (childTree[Q3]->containsObject(object))
			return childTree[Q3]->addObject(object);
		if (childTree[Q4]->containsObject(object))
			return childTree[Q4]->addObject(object);
		return false; //Object was not found to be within one of the cubes, return false.
	}
}



//Check if object origin is within bounds.
bool QuadTree::containsObject(GeometryObject* object) {
	glm::vec3 pos = object->position();
	return	(
				(pos.x < (origin.x + dim.x) && pos.x > (origin.x - dim.x)) &&
				(pos.z < (origin.z + dim.x) && pos.z > (origin.z - dim.x)) &&
				(pos.y > (origin.y + dim.y) && pos.y < (origin.y - dim.y))
			);
}

QuadTree::~QuadTree() {
	if (depth == maxDepth)
		return;
	else {
		delete childTree[Q1];
		delete childTree[Q2];
		delete childTree[Q3];
		delete childTree[Q4];
	}
}