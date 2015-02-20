#ifndef __GEOMETRYOBJECT_H__
#define __GEOMETRYOBJECT_H__

#include "Object.h"
#include "Geometry.h"

/// A game object with renderable Geometry.
class GeometryObject : public Object {
	public:
		/// Create new geometry object.
		/**
		 * @param geometry The Geometry the object should render.
		 */
		GeometryObject(const Geometry* geometry);

		/// Get renderable Geometry.
		/**
		 * @return The renderable Geometry.
		 */
		virtual const Geometry* geometry() const;

		/// Gets the height of the terrain at a given location.
		/**
		* If the position is outside the terrain, 0.0 is returned.
		* @param x X-position in the world.
		* @param z Z-position in the world.
		* @return Height of the terrain.
		*/
		float getY(float x, float z) const;

	private:
		const Geometry* _geometry;
};

#endif