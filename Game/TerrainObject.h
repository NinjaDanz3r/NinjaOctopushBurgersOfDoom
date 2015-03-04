#ifndef __TERRAINOBJECT_H__
#define __TERRAINOBJECT_H__

#include "GeometryObject.h"
#include "Terrain.h"

/** @ingroup game
 * @{
 */

/// A terrain object in the game world.
class TerrainObject : public GeometryObject {
	public:
		/// Create new terrain object.
		/**
		 * @param terrain The Terrain the object should render.
		 */
		TerrainObject(const Terrain* terrain);

		/// Get renderable Geometry.
		/**
		* @return The renderable Geometry.
		*/
		const Geometry* geometry() const;

		/// Gets the height of the terrain at a given location.
		/**
		* If the position is outside the terrain, 0.0 is returned.
		* @param x X-position in the world.
		* @param z Z-position in the world.
		* @return Height of the terrain.
		*/
		float getY(float x, float z) const;

	private:
		const Terrain* terrain;
};

/** @} */

#endif