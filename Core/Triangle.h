#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Core.h"
#include <glm/glm.hpp>

/** @ingroup core
 * @{
 */

/// A triangle.
/**
 * Used for intersection testing.
 */
class Triangle {
	public:
		/// First vertex.
		glm::vec3 v1;

		/// Second vertex.
		glm::vec3 v2;

		/// Third vertex.
		glm::vec3 v3;

		/// Create new triangle.
		/**
		 * @param v1 First vertex.
		 * @param v2 Second vertex.
		 * @param v3 Third vertex.
		 */
		CORE_EXPORT Triangle(const glm::vec3& v1 = { 0.f, 0.f, 0.f }, const glm::vec3& v2 = { 0.f, 0.f, 0.f }, const glm::vec3& v3 = { 0.f, 0.f, 0.f });
};

/** @} */

#endif