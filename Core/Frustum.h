#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include "Core.h"
#include <glm/glm.hpp>

class AABB;
class Rectangle2D;

/** @ingroup core
 * @{
 */

/// A viewing frustum.
/**
 * Used for frustum culling.
 */
class Frustum {
	public:
		/// Create new frustum.
		/**
		 * @param matrix View-projection matrix to create frustum planes from.
		 */
		CORE_EXPORT Frustum(const glm::mat4& matrix);

		/// Check collision between frustum and an AABB.
		/**
		 * @param aabb The AABB to check collision against.
		 * @return Whether there was a collision
		 */
		CORE_EXPORT bool collide(const AABB& aabb) const;

		/// Check collision between frustum and a rectangle.
		/**
		* @param rectangle The rectangle to check collision against.
		* @return Whether there was a collision
		*/
		CORE_EXPORT bool collide(const Rectangle2D& rectangle, const float height) const;

	private:
		glm::vec4 planes[6];

		// The distance returned is the signed distance in normal vector units.
		// To ensure the "true" distance the plane equation has to be normalized.
		static float distanceToPoint(const glm::vec4& plane, const glm::vec3& point);
};

/** @} */

#endif