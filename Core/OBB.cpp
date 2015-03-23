#include "OBB.h"

OBB::OBB(const AABB& aabb, const glm::mat4& matrix) {
	//Transform basis vector by model matrix to create new basis in worldspace.
	glm::vec3 u,v,w;

	//dimensions*id matrix
	u = glm::vec3(matrix*(glm::vec4(dimensions.x, 0.f, 0.f, 0.f)));
	v = glm::vec3(matrix*(glm::vec4(0.f, dimensions.y, 0.f, 0.f)));
	w = glm::vec3(matrix*(glm::vec4(0.f, 0.f, dimensions.z, 0.f)));
	
	dimensions = glm::vec3(u.length(), v.length(), w.length());

	e1 = glm::normalize(u);
	e2 = glm::normalize(v);
	e3 = glm::normalize(w);
}