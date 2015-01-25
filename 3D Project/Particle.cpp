#include "Particle.h"
#include <vector>

Particle::Particle()
{
	texture = new Texture("..\3D Project\Resources\Resources\Textures");
}

Particle::~Particle()
{
	delete texture;
}