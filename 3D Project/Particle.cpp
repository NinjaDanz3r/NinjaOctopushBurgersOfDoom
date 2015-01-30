#include "Particle.h"
#include <vector>

Particle::Particle(){
	texture = new Texture2D("Resources/Textures/kaleido.tga");
	worldPos = glm::vec3(0, 0, 0);
}

Particle::Particle(glm::vec3 worldPos, Texture* texture){
	this->worldPos = worldPos;
	this->texture = texture;
}

Particle::~Particle(){
	delete texture;
}