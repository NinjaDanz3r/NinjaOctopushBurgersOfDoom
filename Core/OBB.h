#ifndef __OBB_H__
#define __OBB_H__

#include "Core.h"
#include <glm/glm.hpp>

/// Oriented bounding box.
/**
 * Used for intersection testing and collision detection.
 */
class OBB {
	public:
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

#endif