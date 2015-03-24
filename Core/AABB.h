#ifndef __AABB_H__
#define __AABB_H__

#include "Core.h"
#include <glm/glm.hpp>

class Frustum;
class Rectangle2D;

/** @ingroup core
 * @{
 */

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

		/// Create new axis-aligned bounding box.
		/**
		 * Create infinitely high axis-aligned bounding box from a 2D rectangle.
		 * Useful for frustum culling.
		 * @param rectangle The rectangle to base the AABB on.
		 * @param height Height.
		 */
		CORE_EXPORT AABB(const Rectangle2D& rectangle, const float height);

		/// Check collision between AABB and a frustum.
		/**
		* @param frustum The Frustum to check collision against.
		* @return Whether there was a collision
		*/
		CORE_EXPORT bool collide(const Frustum& frustum) const;
};

/** @} */

#endif