#include "Ray.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>

#define EPSILON 0.00001

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) {
	this->origin = origin;
	this->direction = direction;
}

float Ray::intersect(const Triangle& triangle) {
	// Declaration
	glm::vec3 edge1, edge2, normal, P, Q, T;
	float det, inverseDet, u, v, t;

	// Find triangle edge vectors
	edge1 = triangle.v2 - triangle.v1;
	edge2 = triangle.v3 - triangle.v1;
	normal = glm::cross(edge1, edge2);

	// Minor optimization, cull if backface (Occurs when inside a model)
	if (glm::dot(-direction, normal) >= 0.0f) {
		// Determinant calculation
		P = glm::cross(direction, edge2);
		det = glm::dot(edge1, P);

		// If determinant is near zero, ray is in the triangle plane.
		if ((det > -EPSILON) && (det < EPSILON))
			return -1.f;
		inverseDet = 1.0f / det;

		T = origin - triangle.v1;	// Distance from v1 to ray origin.
		// Triangle U, V testing.
		u = dot(T, P) *inverseDet;
		if ((u < 0.0f) || (u > 1.0f))
			return -1.f;

		Q = cross(T, edge1);

		v = dot(direction, Q)*inverseDet;
		if ((v <0.0f) || ((u + v) > 1.0f))
			return -1.f;

		t = glm::dot(edge2, Q)*inverseDet;

		// If all attempts to cull the ray has been passed, we have an intersection.
		if (t > EPSILON){
			return t;
		}
	}
	return -1.f;
}

float Ray::intersect(const OBB& obb) {
	float tMin, tMax, t1, t2;
	tMin = std::numeric_limits<float>::lowest();
	tMax = std::numeric_limits<float>::max();

	glm::vec3 vArr[3] = { obb.e1, obb.e2, obb.e3 };
	float dArr[3] = { obb.dimensions.x / 2, obb.dimensions.y / 2, obb.dimensions.z / 2 };
	glm::vec3 P = obb.origin - origin;

	for (int i = 0; i < 3; i++){
		float e = glm::dot(vArr[i], P);
		float f = glm::dot(vArr[i], direction);
		if (fabs(f) > EPSILON) {
			t1 = (e + dArr[i]) / f;
			t2 = (e - dArr[i]) / f;
			if (t1 > t2)
				std::swap(t1, t2);
			if (t1 > tMin)
				tMin = t1;
			if (t2 < tMax)
				tMax = t2;
			if (tMin > tMax)
				return false;
			if (tMax < 0)
				return false;
		} else if ((-e - dArr[i] > 0) || (-e + dArr[i] < 0)) {
			return false;
		}
	}

	if (tMin > 0.f) {
		return tMin;
	} else {
		return tMax;
	}
}

float Ray::intersect(const AABB& box) {
	glm::vec3 inverseRay = (1.0f / direction);
	float t1, t2, t3, t4, t5, t6;
	t1 = (box.minVertex.x - origin.x) * inverseRay.x;
	t2 = (box.maxVertex.x - origin.x) * inverseRay.x;

	t3 = (box.minVertex.y - origin.y) * inverseRay.y;
	t4 = (box.maxVertex.y - origin.y) * inverseRay.y;

	t5 = (box.minVertex.z - origin.z) * inverseRay.z;
	t6 = (box.maxVertex.z - origin.z) * inverseRay.z;

	float tMin, tMax;
	tMin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	tMax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// If tMax < 0, ray is intersecting AABB, but whole AABB is behind us.
	if (tMax < 0.f) {
		return -1.f;
	}

	// If tMin > tMax, ray doesn't intersect AABB.
	if (tMin > tMax) {
		return -1.f;
	}
	return tMin;
}