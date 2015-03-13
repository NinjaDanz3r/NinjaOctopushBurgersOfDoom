#ifndef __INTERSECTIONTESTING_H__
#define __INTERSECTIONTESTING_H__

#include "Core.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>
#include "Ray.h"
#include "Triangle.h"
#include "AABB.h"
#include "OBB.h"

/** @ingroup core
* @{
*/

#define EPSILON 0.00001

CORE_EXPORT bool rayVsTri(const Triangle& triangle, const Ray& ray, float& distance);

CORE_EXPORT bool rayVsOBB(const OBB& obb, const Ray& ray, float& distance);

CORE_EXPORT bool rayVsAABB(const AABB& box, const Ray& ray, float& distance);

/** @} */

#endif