#include "QuadTree.h"

#include <Frustum.h>
#include <glm/glm.hpp>

QuadTree::QuadTree(const Rectangle2D & rectangle, float height, int maxDepth) : QuadTree(rectangle, height, 0, maxDepth) {

}

QuadTree::QuadTree(const Rectangle2D & rectangle, float height, int depth, int maxDepth) {
	this->rectangle = rectangle;
	this->depth = depth;
	this->maxDepth = maxDepth;
	this->height = height;

	// If we're at a leaf, we should populate it with objects 
	if (depth == maxDepth) {
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

		childTree[Q1] = new QuadTree(q1Rect, height, nextDepth, maxDepth);
		childTree[Q2] = new QuadTree(q2Rect, height, nextDepth, maxDepth);
		childTree[Q3] = new QuadTree(q3Rect, height, nextDepth, maxDepth);
		childTree[Q4] = new QuadTree(q4Rect, height, nextDepth, maxDepth);
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

void QuadTree::addObject(GeometryObject* object, Rectangle2D rectangle) {
	if (depth == maxDepth){
		objects.push_back(object);
	} else {
		if (childTree[Q1]->rectangle.overlaps(rectangle))
			childTree[Q1]->addObject(object, rectangle);
		if (childTree[Q2]->rectangle.overlaps(rectangle))
			childTree[Q2]->addObject(object, rectangle);
		if (childTree[Q3]->rectangle.overlaps(rectangle))
			childTree[Q3]->addObject(object, rectangle);
		if (childTree[Q4]->rectangle.overlaps(rectangle))
			childTree[Q4]->addObject(object, rectangle);
	}
}

void QuadTree::getObjects(Frustum& frustum, std::map<GeometryObject*, GeometryObject*>& geometryMap) {
	if ((depth == maxDepth) && frustum.collide(rectangle, height)) {
		for (GeometryObject* obj : objects)
			geometryMap[obj] = obj;
	} else if (frustum.collide(rectangle, height)) {
			childTree[Q1]->getObjects(frustum, geometryMap);
			childTree[Q2]->getObjects(frustum, geometryMap);
			childTree[Q3]->getObjects(frustum, geometryMap);
			childTree[Q4]->getObjects(frustum, geometryMap);
	}
}