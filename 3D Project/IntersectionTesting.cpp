#include "IntersectionTesting.h"

//Möller-Trumbore intersection algorithm for triangles.
bool rayVsTri(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 rayDir, glm::vec3 rayOrigin, float& distance) {
	//Declaration
	glm::vec3 edge1, edge2, P, Q, T;
	float det, inverseDet, u, v, t;
	distance = -1.f;

	//Find triangle edge vectors
	edge1 = v2 - v1;
	edge2 = v3 - v1;
	//Determinant calculation
	P = glm::cross(rayDir, edge2);
	det = glm::dot(edge1, P);

	//If determinant is near zero, ray is in the triangle plane.
	if ((det > -EPSILON) && (det < EPSILON))
		return false;
	inverseDet = 1.0f / det;

	T = rayOrigin - v1;			//Distance from v1 to ray origin.
	//triangle U, V testing.
	u = dot(T, P) *inverseDet;
	if ((u < 0.0f) || (u > 1.0f))
		return false;

	Q = cross(T, edge1);
	
	v = dot(rayDir, Q)*inverseDet;
	if ((v <0.0f) || ( (u + v) > 1.0f))
		return false;

	t = glm::dot(edge2, Q)*inverseDet;

	//If all attempts to cull the ray has been passed, we have an intersection
	if (t > EPSILON){
		distance = t;
		return true;
	}
	return false;
}

bool rayVsOBB(OBB obb, glm::vec3 rayDir, glm::vec3 rayOrigin, float& distance) {
	float tMin, tMax, t1, t2;
	tMin = std::numeric_limits<float>::lowest();
	tMax = std::numeric_limits<float>::max();

	glm::vec3 vArr[3];
	float dArr[3];
	vArr[0] = obb.v1; vArr[1] = obb.v2; vArr[2] = obb.v3;
	dArr[0] = obb.dim.x / 2; dArr[1] = obb.dim.y / 2; dArr[2] = obb.dim.z / 2;
	glm::vec3 P = obb.origin - rayOrigin;

	for (int i = 0; i < 3; i++){
		float e = glm::dot(vArr[i], P);
		float f = glm::dot(vArr[i], rayDir);
		if (fabs(f) > EPSILON)
		{
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
		}
		else if ((-e - dArr[i] > 0) || (-e + dArr[i] < 0))
			return false;
	}
	if ((tMin > 0)) {
		distance = tMin;
		return true;
	}
	else {
		distance = tMax;
		return true;
	}
	return false;
}

//
//bool rayVsTri(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 rayDir, glm::vec3 rayOrigin, float& distance) {
//	glm::vec3 e1 = v2 - v1;
//	glm::vec3 e2 = v3 - v1;
//	glm::vec3 q = glm::cross(rayDir, e2);
//	
//	float a = glm::dot(e1, q);
//	if ((a > -EPSILON) && (a < EPSILON))
//		return false;
//	float f = 1 / a;
//	glm::vec3 s = rayOrigin - v1;
//	float u = f*(glm::dot(s, q));
//	if (u < 0.0f)
//		return false;
//	glm::vec3 r = glm::cross(s, e1);
//	float v = f*glm::dot(rayDir, r);
//	if ((v < 0.0f) || ((u + v) > 1.0))
//		return false;
//	if (f*glm::dot(e2, r) > EPSILON){
//		distance = (f*glm::dot(e2, r));
//		return true;
//	}
//	return false;
//}
