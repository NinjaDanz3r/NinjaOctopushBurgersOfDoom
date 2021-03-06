#include "ParticleScene.h"

#include <gl/glew.h>

#include <Texture2D.h>

#include <Shader.h>
#include <ShaderProgram.h>
#include "Player.h"
#include "ParticleSystem.h"
#include "Camera.h"
#include "input.h"
#include "Scene.h"

#include <glm/glm.hpp>

ParticleScene::ParticleScene() {
	vertexShader = new Shader("particle_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("particle_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("particle_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });
	
	texture = new Texture2D("Resources/Textures/flame.tga");
	particleSystem = new ParticleSystem(shaderProgram, texture, glm::vec3(0.f, 0.f, -10.f), 1000, 0.01, 0.02, 5.f, 1.f);

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

	if (input::triggered(input::NEW_SCENE))
		return new Scene::SceneEnd(SceneEnd::NEW_SCENE);

	return nullptr;
}

void ParticleScene::render(int width, int height) {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	particleSystem->render(width, height, player->camera());
}