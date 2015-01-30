#ifndef __PARTICLE_H__
#define __PARTICLE_H__
#include <glm\glm.hpp>
#include "Texture.h"

//Particle
class Particle
{
public:
	//Constructor
	Particle();
	//Destructor
	~Particle();
private:
	glm::vec3 worldPos;
	Texture* texture;
};

#endif