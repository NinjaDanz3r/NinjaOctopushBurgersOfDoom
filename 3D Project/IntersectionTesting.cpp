#include "IntersectionTesting.h"

//Möller-Trumbore intersection algorithm for triangles.
bool rayVsTri(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 rayDir, glm::vec3 rayOrigin, float& distance) {
	//Declaration
	glm::vec3 edge1, edge2, normal, P, Q, T;
	float det, inverseDet, u, v, t;
	distance = -1.f;

	//Find triangle edge vectors
	edge1 = v2 - v1;
	edge2 = v3 - v1;
	normal = glm::cross(edge1, edge2);

	//Minor optimization, cull if backface (Occurs when inside a model)
	if (glm::dot(-rayDir, normal ) >= 0.0f)
	{
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
		if ((v <0.0f) || ((u + v) > 1.0f))
			return false;

		t = glm::dot(edge2, Q)*inverseDet;

		//If all attempts to cull the ray has been passed, we have an intersection
		if (t > EPSILON){
			distance = t;
			return true;
		}
		return false;
	}
	else
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

bool rayVsAABB(AABB box, glm::vec3 rayDir, glm::vec3 rayOrigin, float& distance){
	distance = -1;
	glm::vec3 inverseRay = (1.0f / rayDir);
	float t1, t2, t3, t4, t5, t6;
	t1 = (box.minVertices.x - rayOrigin.x)*inverseRay.x;
	t2 = (box.maxVertices.x - rayOrigin.x)*inverseRay.x;
	
	t3 = (box.minVertices.y - rayOrigin.y)*inverseRay.y;
	t4 = (box.maxVertices.y - rayOrigin.y)*inverseRay.y;

	t5 = (box.minVertices.z - rayOrigin.z)*inverseRay.z;
	t6 = (box.maxVertices.z - rayOrigin.z)*inverseRay.z;

	float tmin, tmax;
	tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	if (tmax < 0)
	{
		distance = tmax;
		return false;
	}
	
	if (tmin > tmax)
	{
		distance = tmin;
		return false;
	}
	distance = tmin;
	return true;
}