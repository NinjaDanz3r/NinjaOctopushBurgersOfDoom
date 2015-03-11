#include "ParticleSystem.h"
#include <vector>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

ParticleSystem::ParticleSystem(ShaderProgram* shaderProgram, Texture* texture, glm::vec3 origin, int maxParticleCount, int chanceToEmit, float maxVelocity, float maxLifeTime) {
	this->shaderProgram = shaderProgram;
	this->texture = texture;

	particleOrigin = origin;
	this->maxParticleCount = maxParticleCount;
	this->chanceToEmit = chanceToEmit;
	this->maxVelocity = maxVelocity;
	this->maxLifeTime = maxLifeTime;
	particleCount = 0;

	bindPointData();
}

ParticleSystem::~ParticleSystem() {
	glDeleteBuffers(1, &vertexBuffer);
}

unsigned int ParticleSystem::getParticleCount() {
	return particleCount;
}

unsigned int ParticleSystem::getMaxParticleCount() {
	return maxParticleCount;
}

void ParticleSystem::update(double time) {
	if (!this->particlePositions.empty()) {
		for (std::vector<int>::size_type i = 0; i != particleProperties.size(); i++) {
			if (particleProperties[i].lifetime > maxLifeTime) {
				particlePositions.erase(particlePositions.begin() + i);
				particleProperties.erase(particleProperties.begin() + i);
				particleCount--;
				i--;
			} else {
				particlePositions[i].worldPos += static_cast<float>(time)* particleProperties[i].velocity;
				particleProperties[i].lifetime += static_cast<float>(time);
			}
		}
	}
	emitParticle();

	if (particleCount > 0)
		glBufferData(GL_ARRAY_BUFFER, particleCount * sizeof(ParticleSystem::ParticlePosition), &this->particlePositions[0], GL_DYNAMIC_DRAW);
}

void ParticleSystem::render(int width, int height, const Camera* camera) {
	shaderProgram->use();

	glUniform1i(shaderProgram->uniformLocation("baseImage"), 0);

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());

	glBindVertexArray(vertexAttribute);

	// Base image texture
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());

	// Send the matrices to the shader.
	glm::mat4 view =camera->view();

	glUniformMatrix4fv(shaderProgram->uniformLocation("viewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &camera->projection(width, height)[0][0]);

	// Draw the triangles
	glDrawArrays(GL_POINTS, 0, getParticleCount());
}

void ParticleSystem::bindPointData() {
	// Vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// Define vertex data layout
	glGenVertexArrays(1, &vertexAttribute);
	glBindVertexArray(vertexAttribute);
	glEnableVertexAttribArray(0); //the vertex attribute object will remember its enabled attributes

	GLuint vertexPos = shaderProgram->attributeLocation("vertex_position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleSystem::ParticlePosition), BUFFER_OFFSET(0));
}

void ParticleSystem::emitParticle() {
	if ((rand() % 1000 < chanceToEmit) && (particleCount < maxParticleCount)) {
		ParticlePosition newPosition;
		ParticleProperty newProperty;

		newPosition.worldPos = particleOrigin;
		newProperty.lifetime = 0.f - static_cast<float>(rand() % static_cast<int>(maxLifeTime * 2));
		newProperty.velocity.x = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));
		newProperty.velocity.y = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));
		newProperty.velocity.z = static_cast<float>(rand() % (2 * static_cast<int>(maxVelocity)) - static_cast<int>(maxVelocity));

		particlePositions.push_back(newPosition);
		particleProperties.push_back(newProperty);

		particleCount++;
	}
}