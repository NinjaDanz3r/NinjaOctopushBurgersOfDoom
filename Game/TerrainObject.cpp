#include "TerrainObject.h"
#include "Terrain.h"

TerrainObject::TerrainObject(const Terrain* terrain) : GeometryObject(terrain) {
	this->terrain = terrain;
}

const Geometry* TerrainObject::geometry() const {
	return terrain;
}

float TerrainObject::getY(float x, float z) const {
	float xInTerrain = (x - position().x) / scale().x + 0.5f;
	float zInTerrain = (z - position().z) / scale().z + 0.5f;

	return terrain->getY(xInTerrain, zInTerrain) * scale().y + position().y;
}