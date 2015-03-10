#ifndef __INTERSECTIONTESTING_H__
#define __INTERSECTIONTESTING_H__

#include <gl/glew.h>
#include <gl/GL.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>

#define EPSILON 0.00001

class AABB
{
public:
	glm::vec3 v1, v2, origin;
	AABB(glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _origin) {
		v1 = _v1;
		v2 = _v2;
		origin = _origin;
	};
};

class OBB
{
public:
	glm::vec3 v1, v2, v3, origin, dim; //Dim: width, heigh, depth
};

bool rayVsTri(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 rayDir, glm::vec3 rayOrigin, float& distance);

bool rayVsOBB(OBB obb, glm::vec3 rayDir, glm::vec3 rayOrigin, float& distance);

bool rayVsAABB(AABB Box, float x, float y);

#endif