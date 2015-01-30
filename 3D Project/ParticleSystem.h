#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__
#include "ParticleEmitter.h"
#include <vector>
#include <glm\glm.hpp>

//Emitter Controller
class ParticleSystem
{
public:
	//Constructor
	ParticleSystem();
	//Destructor
	~ParticleSystem();

	//Create an emitter
	void createEmitter(const char* texturePath, glm::vec3 worldPos);
private:
	std::vector < ParticleEmitter > emitters;
};

#endif