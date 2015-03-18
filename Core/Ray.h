#ifndef __RAY_H__
#define __RAY_H__

#include "Core.h"
#include <glm/glm.hpp>

class Triangle;
class OBB;
class AABB;

/** @ingroup core
 * @{
 */

/// A ray.
/**
 * Used for intersection testing.
 */
class Ray {
	public:
		/// Origin.
		glm::vec3 origin;

		/// Direction
		glm::vec3 direction;

		/// Create new ray.
		/**
		 * @param origin Origin.
		 * @param direction Direction.
		 */
		CORE_EXPORT Ray(const glm::vec3& origin = { 0.f, 0.f, 0.f }, const glm::vec3& direction = { 0.f, 0.f, 0.f });

		/// Checks intersection between the ray and a Triangle.
		/**
		 * Uses the M&ouml;ller-Trumbore intersection algorithm for triangles.
		 * @param triangle Triangle to check intersection against.
		 * @return Distance to Triangle (or -1 if missed)
		 */
		CORE_EXPORT float intersect(const Triangle& triangle) const;

		/// Checks intersection between the ray and an OBB.
		/**
		 * @param obb OBB to check intersection against.
		 * @return Distance to OBB (or -1 if missed)
		 */
		CORE_EXPORT float intersect(const OBB& obb) const;

		/// Checks intersection between the ray and an AABB.
		/**
		 * @param aabb AABB to check intersection against.
		 * @return Distance to AABB (or -1 if missed)
		 */
		CORE_EXPORT float intersect(const AABB& aabb) const;
};

/** @} */

#endif