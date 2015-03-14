#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Core.h"
#include <glm/glm.hpp>

class Frustum;

/** @ingroup core
 * @{
 */

/// 2D rectangle.
/**
 * Used for view frustum culling.
 */
class Rectangle2D {
	public:
		/// Origin.
		glm::vec2 origin;

		/// Dimensions.
		glm::vec2 dimensions;

		/// Create new rectangle.
		/**
		 * @param origin Origin.
		 * @param dimensions Dimensions.
		 */
		CORE_EXPORT Rectangle2D(const glm::vec2& origin = { 0.f, 0.f }, const glm::vec2& dimensions = { 0.f, 0.f });

		/// Check collision between rectangle and a Frustum.
		/**
		* @param frustum The Frustum to check collision against.
		* @return Whether there was a collision
		*/
		CORE_EXPORT bool collide(const Frustum& frustum) const;
};

/** @} */

#endif