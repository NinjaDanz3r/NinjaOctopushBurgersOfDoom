#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include "Core.h"
#include <glm/glm.hpp>

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
		CORE_EXPORT Frustum(const glm::mat4x4& matrix);

	private:
		glm::vec4 planes[6];
};

/** @} */

#endif