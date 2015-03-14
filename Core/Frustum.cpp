#include "Frustum.h"

Frustum::Frustum(const glm::mat4& matrix) {
	// Left clipping plane
	planes[0].x = matrix[0][3] + matrix[0][0];
	planes[0].y = matrix[1][3] + matrix[1][0];
	planes[0].z = matrix[2][3] + matrix[2][0];
	planes[0].w = matrix[3][3] + matrix[3][0];

	// Right clipping plane
	planes[1].x = matrix[0][3] - matrix[0][0];
	planes[1].y = matrix[1][3] - matrix[1][0];
	planes[1].z = matrix[2][3] - matrix[2][0];
	planes[1].w = matrix[3][3] - matrix[3][0];

	// Top clipping plane
	planes[2].x = matrix[0][3] - matrix[0][1];
	planes[2].y = matrix[1][3] - matrix[1][1];
	planes[2].z = matrix[2][3] - matrix[2][1];
	planes[2].w = matrix[3][3] - matrix[3][1];

	// Bottom clipping plane
	planes[3].x = matrix[0][3] + matrix[0][1];
	planes[3].y = matrix[1][3] + matrix[1][1];
	planes[3].z = matrix[2][3] + matrix[2][1];
	planes[3].w = matrix[3][3] + matrix[3][1];

	// Near clipping plane
	planes[4].x = matrix[0][3] + matrix[0][2];
	planes[4].y = matrix[1][3] + matrix[1][2];
	planes[4].z = matrix[2][3] + matrix[2][2];
	planes[4].w = matrix[3][3] + matrix[3][2];

	// Far clipping plane
	planes[5].x = matrix[0][3] - matrix[0][2];
	planes[5].y = matrix[1][3] - matrix[1][2];
	planes[5].z = matrix[2][3] - matrix[2][2];
	planes[5].w = matrix[3][3] - matrix[3][2];
}

bool Frustum::collide(const AABB& aabb) const {
	// Define the AABB's vertices.
	glm::vec3 vertices[8];
	vertices[0] = aabb.minVertex;
	vertices[1] = aabb.minVertex + glm::vec3(aabb.dimensions.x, 0.f, 0.f);
	vertices[2] = aabb.minVertex + glm::vec3(0.f, aabb.dimensions.y, 0.f);
	vertices[3] = aabb.minVertex + glm::vec3(0.f, 0.f, aabb.dimensions.z);
	vertices[4] = aabb.maxVertex;
	vertices[5] = aabb.maxVertex - glm::vec3(aabb.dimensions.x, 0.f, 0.f);
	vertices[6] = aabb.maxVertex - glm::vec3(0.f, aabb.dimensions.y, 0.f);
	vertices[7] = aabb.maxVertex - glm::vec3(0.f, 0.f, aabb.dimensions.z);

	// Check if the AABB's vertices lie in the planes or in their positive halfspaces.
	// Only one vertex has to lie inside the halfspace for each plane.
	for (int plane = 0; plane < 6; plane++) {
		bool inside = false;
		for (int vertex = 0; vertex < 8; vertex++) {
			if (distanceToPoint(planes[plane], vertices[vertex]) >= 0.f) {
				inside = true;
				break;
			}
		}

		if (!inside)
			return false;
	}
	return true;
}

float Frustum::distanceToPoint(const glm::vec4& plane, const glm::vec3& point) {
	return plane.x * point.x + plane.y * point.y + plane.z * point.z + plane.w;
}