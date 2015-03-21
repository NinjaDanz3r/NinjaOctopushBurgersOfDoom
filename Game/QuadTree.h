#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <Rectangle2D.h>
#include <vector>
#include <map>

class QuadTree;
class GeometryObject;
class Frustum;

class QuadTree {
	public:
		QuadTree(const Rectangle2D & _rect, int _depth, int _maxDepth);
		~QuadTree();
		void addObject(GeometryObject* object, Rectangle2D rect);
		void getObjects(Frustum& frustum, std::map<GeometryObject*, GeometryObject*>& GeometryMap);
		unsigned int getNumberOfObjects();

	private:
		// Enum to make spatial relations more intuitive.
		enum Directions {
			Q1 = 0, // First quadrant, northwest
			Q2,		// Second quadrant, northeast
			Q3,		// Third quadrant, southeast
			Q4		// Fourth quadrant, southwest
		};

		Rectangle2D rectangle;

		QuadTree* childTree[4];
		
		unsigned int depth;
		unsigned int maxDepth;
		std::vector<GeometryObject*> objects;
		bool isLeaf;
};

#endif