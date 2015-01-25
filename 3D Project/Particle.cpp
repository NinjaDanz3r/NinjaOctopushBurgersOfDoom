#include "Particle.h"
#include <vector>

Particle::Particle()
{
	texture = new Texture("..\3D Project\Resources\Resources\Textures");
	worldPos = glm::vec3(0, 0, 0);
}

Particle::~Particle()
{
	delete texture;
}