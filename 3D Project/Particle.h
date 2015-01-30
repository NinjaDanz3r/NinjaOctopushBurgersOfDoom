#ifndef __PARTICLE_H__
#define __PARTICLE_H__
#include <glm\glm.hpp>
#include "Texture2D.h"

//Particle
class Particle
{
public:
	//Constructor
	Particle();
	Particle(glm::vec3 WorldPos, Texture* texture);
	glm::vec3 worldPos;
	Texture* texture;
	//Destructor
	~Particle();
private:
};

#endif