#include "Particle.h"
#include <vector>

Particle::Particle(){
	worldPos = glm::vec3(0.f, 0.f, -1.f);
}

Particle::Particle(glm::vec3 worldPos, Texture* texture){
	this->worldPos = worldPos;
}

Particle::~Particle(){
	//delete texture;
}