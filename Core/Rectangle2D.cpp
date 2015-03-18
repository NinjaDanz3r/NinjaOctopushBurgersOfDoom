#include "Rectangle2D.h"
#include "Frustum.h"

Rectangle2D::Rectangle2D(const glm::vec2& origin, const glm::vec2& dimensions) {
	this->origin = origin;
	this->dimensions = dimensions;
}

bool Rectangle2D::collide(const Frustum& frustum) const {
	return frustum.collide(*this);
}