#include "AABB.h"
#include <limits>

AABB::AABB(const glm::vec3& dimensions, const glm::vec3& origin, const glm::vec3& minVertex, const glm::vec3& maxVertex) {
	this->dimensions = dimensions;
	this->origin = origin;
	this->minVertex = minVertex;
	this->maxVertex = maxVertex;
}

AABB::AABB(const Rectangle& rectangle) {
	this->dimensions = glm::vec3(rectangle.dimensions.x, std::numeric_limits<float>::max(), rectangle.dimensions.y);
	this->origin = glm::vec3(rectangle.origin.x, 0.f, rectangle.origin.y);
	this->minVertex = glm::vec3(rectangle.origin.x - rectangle.dimensions.x / 2.f, std::numeric_limits<float>::lowest() / 2.f, rectangle.origin.y - rectangle.dimensions.y / 2.f);
	this->maxVertex = glm::vec3(rectangle.origin.x + rectangle.dimensions.x / 2.f, std::numeric_limits<float>::max() / 2.f, rectangle.origin.y + rectangle.dimensions.y / 2.f);
}

bool AABB::collide(const Frustum& frustum) const {
	return frustum.collide(*this);
}