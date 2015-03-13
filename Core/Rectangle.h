#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Core.h"
#include <glm/glm.hpp>

/** @ingroup core
* @{
*/

/// 2D rectangle.
/**
 * Used for view frustum culling.
 */
class Rectangle {
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
		CORE_EXPORT Rectangle(const glm::vec2& origin = { 0.f, 0.f }, const glm::vec2& dimensions = { 0.f, 0.f });
};

/** @} */

#endif