#include "GeometryObject.h"

GeometryObject::GeometryObject(const Geometry* geometry) {
	_geometry = geometry;
}

const Geometry* GeometryObject::geometry() const {
	return _geometry;
}