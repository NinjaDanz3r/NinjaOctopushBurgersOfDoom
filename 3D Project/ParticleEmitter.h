#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__
#include <glm/glm.hpp>

//Emitter of particles
class ParticleEmitter
{
public:
	//Constructors
	ParticleEmitter();
	ParticleEmitter(const char* texturePath, glm::vec3 worldPos);
	//Destructor
	~ParticleEmitter();

private:
	glm::vec3 worldPos;
};

#endif