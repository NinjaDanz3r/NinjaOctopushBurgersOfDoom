#include "Datastructures.h"


QuadTree::QuadTree(const Rectangle2D & _rectangle, int _depth, int _maxDepth) {
	rectangle = _rectangle;
	depth = _depth;
	maxDepth = _maxDepth;
	isLeaf = false;

	//childTree[Q1] = childTree[Q2] = childTree[Q3] = childTree[Q4] = nullptr;
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

	Rectangle2D q1Rect(glm::vec2(rectangle.origin.x - quarterWidth, rectangle.origin.y + quarterHeight), quadrantDim);
	Rectangle2D q2Rect(glm::vec2(rectangle.origin.x + quarterWidth, rectangle.origin.y + quarterHeight), quadrantDim);
	Rectangle2D q3Rect(glm::vec2(rectangle.origin.x + quarterWidth, rectangle.origin.y - quarterHeight), quadrantDim);
	Rectangle2D q4Rect(glm::vec2(rectangle.origin.x - quarterWidth, rectangle.origin.y - quarterHeight), quadrantDim);

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
bool QuadTree::addObject(GeometryObject* object, Rectangle2D rect) {
	if (depth == maxDepth){
		if (this->rectangle.overlaps(rect)){ 
			//fprintf(stderr,"\nModel added.\n");
			//fprintf(stderr, "This rectangle: X%f,Y%f\nDimensions: X%f,Y%f\n", rectangle.origin.x, rectangle.origin.y, rectangle.dimensions.x, rectangle.dimensions.y);
			//fprintf(stderr, "Other rectangle: X%f,Y%f\nDimensions: X%f,Y%f\n", rect.origin.x, rect.origin.y, rect.dimensions.x, rect.dimensions.y);
			//fflush(stderr);
			objects.push_back(object);
			return true;
		}
		return false;
	}
	else
	{
		bool tempBool[4];
		if (childTree[Q1]->rectangle.overlaps(rect))
			tempBool[0] = childTree[Q1]->addObject(object, rect);
		if (childTree[Q2]->rectangle.overlaps(rect))
			tempBool[0] = childTree[Q2]->addObject(object, rect);
		if (childTree[Q3]->rectangle.overlaps(rect))
			tempBool[0] = childTree[Q3]->addObject(object, rect);
		if (childTree[Q4]->rectangle.overlaps(rect))
			tempBool[0] = childTree[Q4]->addObject(object, rect);

		return (tempBool[0] || tempBool[1] || tempBool[2] || tempBool[3]);
	}
}

void QuadTree::getObjects(Frustum & frustum, std::map<GeometryObject*, GeometryObject*> & GeometryMap) {

	if ( (depth == maxDepth) && (frustum.collide(rectangle)) ){
		if (!objects.empty())
		{
			for (GeometryObject* obj : objects)
				GeometryMap[obj] = obj;
		}
		return;
	}
	else if(frustum.collide(rectangle)){
			childTree[Q1]->getObjects(frustum, GeometryMap);
			childTree[Q2]->getObjects(frustum, GeometryMap);
			childTree[Q3]->getObjects(frustum, GeometryMap);
			childTree[Q4]->getObjects(frustum, GeometryMap);
	}
}

QuadTree::~QuadTree() {
	if (depth == maxDepth)
	{
		objects.clear();
		return;
	}
	else {
		delete childTree[Q1];
		delete childTree[Q2];
		delete childTree[Q3];
		delete childTree[Q4];

	}
}