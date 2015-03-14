#include "Frustum.h"

Frustum::Frustum(const glm::mat4x4& matrix) {
	// Left clipping plane
	planes[0].x = matrix[4][1] + matrix[1][1];
	planes[0].y = matrix[4][2] + matrix[1][2];
	planes[0].z = matrix[4][3] + matrix[1][3];
	planes[0].w = matrix[4][4] + matrix[1][4];

	// Right clipping plane
	planes[1].x = matrix[4][1] - matrix[1][1];
	planes[1].y = matrix[4][2] - matrix[1][2];
	planes[1].z = matrix[4][3] - matrix[1][3];
	planes[1].w = matrix[4][4] - matrix[1][4];

	// Top clipping plane
	planes[2].x = matrix[4][1] - matrix[2][1];
	planes[2].y = matrix[4][2] - matrix[2][2];
	planes[2].z = matrix[4][3] - matrix[2][3];
	planes[2].w = matrix[4][4] - matrix[2][4];

	// Bottom clipping plane
	planes[3].x = matrix[4][1] + matrix[2][1];
	planes[3].y = matrix[4][2] + matrix[2][2];
	planes[3].z = matrix[4][3] + matrix[2][3];
	planes[3].w = matrix[4][4] + matrix[2][4];

	// Near clipping plane
	planes[4].x = matrix[4][1] + matrix[3][1];
	planes[4].y = matrix[4][2] + matrix[3][2];
	planes[4].z = matrix[4][3] + matrix[3][3];
	planes[4].w = matrix[4][4] + matrix[3][4];

	// Far clipping plane
	planes[5].x = matrix[4][1] - matrix[3][1];
	planes[5].y = matrix[4][2] - matrix[3][2];
	planes[5].z = matrix[4][3] - matrix[3][3];
	planes[5].w = matrix[4][4] - matrix[3][4];
}