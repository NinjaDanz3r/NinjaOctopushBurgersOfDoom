#ifndef __INTERSECTIONTESTING_H__
#define __INTERSECTIONTESTING_H__

#include "Core.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>
#include "Ray.h"
#include "Triangle.h"

/** @ingroup core
* @{
*/

#define EPSILON 0.00001

class AABB {
	public:
		glm::vec3 dim, origin, minVertices, maxVertices; //Dim: width, height, depth

		//constructors
		CORE_EXPORT AABB(){};

		CORE_EXPORT AABB(glm::vec3 _dim, glm::vec3 _origin, glm::vec3 _minVertices, glm::vec3 _maxVertices) {
			dim = _dim;
			origin = _origin;
			minVertices = _minVertices;
			maxVertices = _maxVertices;
		};
};

class OBB {
	public:
		glm::vec3 v1, v2, v3, origin, dim; //Dim: width, height, depth
};

CORE_EXPORT bool rayVsTri(const Triangle& triangle, const Ray& ray, float& distance);

CORE_EXPORT bool rayVsOBB(OBB obb, const Ray& ray, float& distance);

CORE_EXPORT bool rayVsAABB(AABB box, const Ray& ray, float& distance);

/** @} */

#endif