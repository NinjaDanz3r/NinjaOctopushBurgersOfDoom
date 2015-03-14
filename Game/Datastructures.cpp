#include "Datastructures.h"


QuadTree::QuadTree(const Rectangle & _rectangle, int _depth, int _maxDepth) {
	rectangle = _rectangle;
	depth = _depth;
	maxDepth = _maxDepth;
	isLeaf = false;

	//If we're at a leaf, we should populate it with objects 
	if (_depth == _maxDepth) {
		isLeaf = true;
		return;
	}

	//Precalculate some values
	float halfWidth = rectangle.dimensions.x / 2.f;
	float quarterWidth = halfWidth / 2.f;
	
	float halfHeight = rectangle.dimensions.y / 2.f;
	float quarterHeight = halfHeight / 2.f;

	glm::vec2 quadrantDim = glm::vec2(halfWidth, halfHeight);
	int nextDepth = depth+1;

	Rectangle q1Rect(glm::vec2(rectangle.origin.x - quarterWidth, rectangle.origin.y + quarterHeight), quadrantDim);
	Rectangle q2Rect(glm::vec2(rectangle.origin.x + quarterWidth, rectangle.origin.y + quarterHeight), quadrantDim);
	Rectangle q3Rect(glm::vec2(rectangle.origin.x + quarterWidth, rectangle.origin.y - quarterHeight), quadrantDim);
	Rectangle q4Rect(glm::vec2(rectangle.origin.x - quarterWidth, rectangle.origin.y - quarterHeight), quadrantDim);

	childTree[Q1] = new QuadTree(q1Rect, nextDepth, maxDepth);
	childTree[Q2] = new QuadTree(q2Rect, nextDepth, maxDepth);
	childTree[Q3] = new QuadTree(q3Rect, nextDepth, maxDepth);
	childTree[Q4] = new QuadTree(q4Rect, nextDepth, maxDepth);
}

//Prints debug information
void QuadTree::debugTree(std::string test)
{
	if (depth == maxDepth)
	{
		fprintf(stderr, "===I'm a leaf node!\n My Data: \n");
		fprintf(stderr, "Depth: %i\n maxDepth: %i\n Origin: %f,%f\n Width: %f\n Height: %f\n\n", depth, maxDepth, rectangle.origin.x, rectangle.origin.y, rectangle.dimensions.x, rectangle.dimensions.y);
		return;
	}
	else
	{
		fprintf(stderr, "===I'm a quadrant node!\n I live at: %s\n My Data: \n", test.c_str());
		fprintf(stderr, "Depth: %i\n maxDepth: %i\n Origin: %f,%f\n Width: %f\n Height: %f\n\n", depth, maxDepth, rectangle.origin.x, rectangle.origin.y, rectangle.dimensions.x, rectangle.dimensions.y);
		childTree[Q1]->debugTree("Q1");
		childTree[Q2]->debugTree("Q2");
		childTree[Q3]->debugTree("Q3");
		childTree[Q4]->debugTree("Q4");
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
		return false; //Object was not found to be within one of the rectangles, return false.
	}
}



//Check if object origin is within bounds.
bool QuadTree::containsObject(GeometryObject* object) {
	glm::vec3 pos = object->position();
	return	(
				//TODO: Foreach point (8) in minimum obb containing object
				(pos.x < (rectangle.origin.x + (rectangle.dimensions.x) / 2.f) && pos.x > (rectangle.origin.x - (rectangle.dimensions.x) / 2.f)) &&
				(pos.z < (rectangle.origin.y + (rectangle.dimensions.y) / 2.f) && pos.z < (rectangle.origin.y - (rectangle.dimensions.y) / 2.f))
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