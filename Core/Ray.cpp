#include "Ray.h"

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) {
	this->origin = origin;
	this->direction = direction;
}