#ifndef __OBB_H__
#define __OBB_H__

#include "Core.h"
#include "AABB.h"
#include <glm/glm.hpp>

/** @ingroup core
 * @{
 */

/// Oriented bounding box.
/**
 * Used for intersection testing and collision detection.
 */
class OBB {
	public:
		/// OBB from AABB constructor
		/**
		* @param aabb AABB to create the OBB from.
		* @param matrix Transformation matrix to apply to the AABB.
		*/
		OBB(const AABB& aabb, const glm::mat4& matrix);

		/// First base vector.
		glm::vec3 e1;

		/// Second base vector.
		glm::vec3 e2;

		/// Third base vector.
		glm::vec3 e3;

		/// Origin.
		glm::vec3 origin;

		/// Dimensions.
		glm::vec3 dimensions;
};

/** @} */

#endif