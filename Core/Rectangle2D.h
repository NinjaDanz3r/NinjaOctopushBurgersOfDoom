#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Core.h"
#include "Model.h"
#include <glm/glm.hpp>

class Frustum;
class Model;
class Rectangle2D;
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
		
		CORE_EXPORT Rectangle2D::Rectangle2D(const Model & model, glm::mat4 matrix);

		/// Check collision between rectangle and a Frustum.
		/**
		* @param frustum The Frustum to check collision against.
		* @return Whether there was a collision
		*/
		CORE_EXPORT bool collide(const Frustum& frustum) const;

		/// Check collision between rectangle and a Frustum.
		/**
		* @param rectangle2D The rectangle to check overlap against
		* @return Whether there was an overlap
		*/
		CORE_EXPORT bool overlaps(const Rectangle2D & otherRect);
};

/** @} */

#endif