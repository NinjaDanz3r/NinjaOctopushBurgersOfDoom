#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW\glfw3.h>

#include "Texture2D.h"

#include "ParticleScene.h"

#include "Square.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

ParticleScene::ParticleScene() {
	vertexShader = new Shader("particle_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("particle_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("particle_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });
	//particle = new Particle();
	particleSystem = new ParticleSystem(glm::vec3(0.f, 0.f, -10.f), 400, 1, 6, 1);
	texture = new Texture2D("Resources/Textures/kaleido.tga");

	bindPointData();

	player = new Player();
	player->setMovementSpeed(2.0f);
}

ParticleScene::~ParticleScene() {
	delete player;
	delete texture;
	delete particleSystem;

	delete shaderProgram;
	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;
}

Scene::SceneEnd* ParticleScene::update(double time) {
	player->update(time);
	particleSystem->update(time);
	vertexCount = particleSystem->getParticleCount();

	if (vertexCount > 0)
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(ParticleSystem::ParticlePosition), particleSystem->getStartAddress(), GL_DYNAMIC_DRAW);
	return nullptr;
}

void ParticleScene::render(int width, int height) {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram->shaderProgram());

	glUniform1i(glGetUniformLocation(shaderProgram->shaderProgram(), "baseImage"), 0);

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());

	glBindVertexArray(vertexAttribute);

	// Base image texture
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());

	// Send the matrices to the shader.
	glm::mat4 view = player->camera()->view();

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->shaderProgram(), "viewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->shaderProgram(), "projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);

	// Draw the triangles
	glDrawArrays(GL_POINTS, 0, particleSystem->getParticleCount());
}

void ParticleScene::bindPointData() {
	// Vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// Define vertex data layout
	glGenVertexArrays(1, &vertexAttribute);
	glBindVertexArray(vertexAttribute);
	glEnableVertexAttribArray(0); //the vertex attribute object will remember its enabled attributes

	GLuint vertexPos = glGetAttribLocation(shaderProgram->shaderProgram(), "vertex_position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleSystem::ParticlePosition), BUFFER_OFFSET(0));
}