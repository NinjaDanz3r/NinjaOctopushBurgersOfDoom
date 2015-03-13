#ifndef __RAY_H__
#define __RAY_H__

#include "Core.h"
#include <glm/glm.hpp>

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
};

/** @} */

#endif