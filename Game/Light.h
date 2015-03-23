#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <glm/glm.hpp>

/// A spotlight.
struct Light {
	/// Position.
	glm::vec4 position = glm::vec4(0.f, 3.f, 3.f, 1.f);

	/// Intensity.
	glm::vec3 intensity = glm::vec3(1.f, 1.f, 1.f);

	/// Diffuse koefficient.
	glm::vec3 diffuseKoefficient = glm::vec3(1.f, 1.f, 1.f);
};

#endif