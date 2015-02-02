#include "Particle.h"
#include <vector>

Particle::Particle(){
	worldPos = glm::vec3(0.f, 0.f, 10.f);
}

Particle::Particle(glm::vec3 worldPos, Texture* texture){
	this->worldPos = worldPos;
	//this->texture = texture;
}

Particle::~Particle(){
	//delete texture;
}