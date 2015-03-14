#ifndef __AABB_H__
#define __AABB_H__

#include "Core.h"
#include <glm/glm.hpp>
#include "Frustum.h"

/** @ingroup core
* @{
*/

class Frustum;

/// An axis-aligned bounding box.
/**
 * Used for intersection testing.
 */
class AABB {
	public:
		/// Dimensions.
		glm::vec3 dimensions;

		/// Origin.
		glm::vec3 origin;

		/// Min vertex.
		glm::vec3 minVertex;

		/// Max vertex.
		glm::vec3 maxVertex;

		/// Create new axis-aligned bounding box.
		/**
		 * @param dimensions Dimensions.
		 * @param origin Origin.
		 * @param minVertex Min vertex.
		 * @param maxVertex Max vertex.
		 */
		CORE_EXPORT AABB(const glm::vec3& dimensions = { 0.f, 0.f, 0.f }, const glm::vec3& origin = { 0.f, 0.f, 0.f }, const glm::vec3& minVertex = { 0.f, 0.f, 0.f }, const glm::vec3& maxVertex = { 0.f, 0.f, 0.f });

		/// Check collision between AABB and a frustum.
		/**
		* @param frustum The Frustum to check collision against.
		* @return Whether there was a collision
		*/
		CORE_EXPORT bool collide(const Frustum& frustum) const;
};

/** @} */

#endif