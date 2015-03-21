#include "QuadTree.h"

QuadTree::QuadTree(const Rectangle2D & _rectangle, int _depth, int _maxDepth) {
	rectangle = _rectangle;
	depth = _depth;
	maxDepth = _maxDepth;

	// If we're at a leaf, we should populate it with objects 
	if (_depth == _maxDepth) {
		isLeaf = true;
	} else {
		// Precalculate some values
		float halfWidth = rectangle.dimensions.x / 2.f;
		float quarterWidth = halfWidth / 2.f;

		float halfHeight = rectangle.dimensions.y / 2.f;
		float quarterHeight = halfHeight / 2.f;

		glm::vec2 quadrantDim = glm::vec2(halfWidth, halfHeight);
		int nextDepth = depth + 1;

		Rectangle2D q1Rect(glm::vec2(rectangle.origin.x - quarterWidth, rectangle.origin.y + quarterHeight), quadrantDim);
		Rectangle2D q2Rect(glm::vec2(rectangle.origin.x + quarterWidth, rectangle.origin.y + quarterHeight), quadrantDim);
		Rectangle2D q3Rect(glm::vec2(rectangle.origin.x + quarterWidth, rectangle.origin.y - quarterHeight), quadrantDim);
		Rectangle2D q4Rect(glm::vec2(rectangle.origin.x - quarterWidth, rectangle.origin.y - quarterHeight), quadrantDim);

		childTree[Q1] = new QuadTree(q1Rect, nextDepth, maxDepth);
		childTree[Q2] = new QuadTree(q2Rect, nextDepth, maxDepth);
		childTree[Q3] = new QuadTree(q3Rect, nextDepth, maxDepth);
		childTree[Q4] = new QuadTree(q4Rect, nextDepth, maxDepth);
	}
}

void QuadTree::addObject(GeometryObject* object, Rectangle2D rect) {
	if (depth == maxDepth){
		objects.push_back(object);
	} else {
		if (childTree[Q1]->rectangle.overlaps(rect))
			childTree[Q1]->addObject(object, rect);
		if (childTree[Q2]->rectangle.overlaps(rect))
			childTree[Q2]->addObject(object, rect);
		if (childTree[Q3]->rectangle.overlaps(rect))
			childTree[Q3]->addObject(object, rect);
		if (childTree[Q4]->rectangle.overlaps(rect))
			childTree[Q4]->addObject(object, rect);
	}
}

void QuadTree::getObjects(Frustum & frustum, std::map<GeometryObject*, GeometryObject*> & GeometryMap) {
	if ((depth == maxDepth) && frustum.collide(rectangle)) {
		for (GeometryObject* obj : objects)
			GeometryMap[obj] = obj;
	} else if (frustum.collide(rectangle)) {
			childTree[Q1]->getObjects(frustum, GeometryMap);
			childTree[Q2]->getObjects(frustum, GeometryMap);
			childTree[Q3]->getObjects(frustum, GeometryMap);
			childTree[Q4]->getObjects(frustum, GeometryMap);
	}
}

QuadTree::~QuadTree() {
	if (depth == maxDepth) {
		objects.clear();
	} else {
		delete childTree[Q1];
		delete childTree[Q2];
		delete childTree[Q3];
		delete childTree[Q4];
	}
}