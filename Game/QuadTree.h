#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <Rectangle2D.h>
#include <vector>
#include <map>

class QuadTree;
class GeometryObject;
class Frustum;

/** @ingroup game
* @{
*/

/// A quad tree. Used for frustum culling.
class QuadTree {
	public:
		/// Create new quad tree.
		/**
		 * The amount of leaf nodes is 4^maxDepth.
		 * @param rectangle Rectangle the quad tree should be contained in.
		 * @param height Height of the quad tree.
		 * @param maxDepth Depth of the quad tree to be created.
		 */
		QuadTree(const Rectangle2D& rectangle, float height, int maxDepth);

		/// Destructor.
		~QuadTree();

		/// Add an object to the quad tree.
		/**
		 * @param object %Object to add.
		 * @param rectangle Rectangle in which object is contained.
		 */
		void addObject(GeometryObject* object, Rectangle2D rectangle);

		/// Get objects in the quad tree inside a frustum.
		/**
		 * Note: This method adds objects to the map if they are contained in a quad which intersects the frustum.
		 * The object's AABB is not checked.
		 * @param frustum Frustum that objects should intersect.
		 * @param geometryMap Map of geometry objects to add intersecting objects to.
		 */
		void getObjects(Frustum& frustum, std::map<GeometryObject*, GeometryObject*>& geometryMap);

	private:
		// Enum to make spatial relations more intuitive.
		enum Directions {
			Q1 = 0, // First quadrant, northwest
			Q2,		// Second quadrant, northeast
			Q3,		// Third quadrant, southeast
			Q4		// Fourth quadrant, southwest
		};

		QuadTree(const Rectangle2D& rectangle, float height, int depth, int maxDepth);

		Rectangle2D rectangle;

		QuadTree* childTree[4];
		float height;
		
		unsigned int depth;
		unsigned int maxDepth;
		std::vector<GeometryObject*> objects;
		bool isLeaf;
};

/** @} */

#endif