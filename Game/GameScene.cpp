#include "GameScene.h"
#include <gl/glew.h>

#include "FrameBufferObjects.h"

#include <Model.h>
#include "GeometryObject.h"
#include <Texture2D.h>

#include "settings.h"
#include "input.h"

#include <Shader.h>
#include <ShaderProgram.h>
#include "Camera.h"
#include "Player.h"
#include "ParticleSystem.h"

#include "SoundSystem.h"
#include "Listener.h"
#include "WaveFile.h"
#include "SoundBuffer.h"
#include "Sound.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

GameScene::GameScene() {
	diffuse = new Texture2D("Resources/Models/rock01/diffuse.tga");
	normal = new Texture2D("Resources/Models/rock01/normal.tga");
	specular = new Texture2D("Resources/Models/rock01/specular.tga");

	vertexShader = new Shader("default_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("default_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("normalspecularmap_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	deferredVertexShader = new Shader("deferred_vertex.glsl", GL_VERTEX_SHADER);
	deferredFragmentShader = new Shader("deferred_fragment.glsl", GL_FRAGMENT_SHADER);
	deferredShaderProgram = new ShaderProgram({ deferredVertexShader, deferredFragmentShader });

	particleVertexShader = new Shader("particle_vertex.glsl", GL_VERTEX_SHADER);
	particleGeometryShader = new Shader("particle_geometry.glsl", GL_GEOMETRY_SHADER);
	particleFragmentShader = new Shader("particle_fragment.glsl", GL_FRAGMENT_SHADER);
	particleShaderProgram = new ShaderProgram({ particleVertexShader, particleGeometryShader, particleFragmentShader });

	geometry = new Model("Resources/Models/Rock.bin");
	geometryObject = new GeometryObject(geometry);
	geometryObject->setScale(0.01f, 0.01f, 0.01f);
	geometryObject->setPosition(glm::vec3(10.0f, 0.0f, 0.0f));

	particleTexture = new Texture2D("Resources/Textures/flame.tga");
	particleSystem = new ParticleSystem(particleShaderProgram, particleTexture, glm::vec3(0.f, 0.f, 0.f), 1000, 0.01, 0.02, 5.f, 1.f);

	player = new Player();
	player->setMovementSpeed(2.0f);
	multipleRenderTargets = new FrameBufferObjects(deferredShaderProgram, settings::displayWidth(), settings::displayHeight());

	waveFile = new WaveFile("Resources/Audio/DontBurnTheRock.wav");
	buffer = new SoundBuffer(waveFile);
	sound = new Sound(buffer);
	sound->setGain(2.f);
	sound->play();
}

GameScene::~GameScene() {
	delete diffuse;
	delete normal;
	delete specular;

	delete particleTexture;
	delete particleSystem;

	delete multipleRenderTargets;
	delete deferredShaderProgram;
	delete shaderProgram;
	delete particleShaderProgram;

	delete deferredVertexShader;
	delete deferredFragmentShader;

	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	delete particleVertexShader;
	delete particleGeometryShader;
	delete particleFragmentShader;

	delete geometryObject;
	delete geometry;
	delete player;

	delete sound;
	delete buffer;
	delete waveFile;
}

Scene::SceneEnd* GameScene::update(double time) {
	player->update(time);
	particleSystem->update(time);

	geometryObject->move(glm::vec3(-static_cast<float>(time), 0.0f, 0.0f));

	if (input::triggered(input::CHANGE_RENDER_STATE))
		geometryObject->setPosition(glm::vec3(10.f, 0.0f, 0.0f));

	if (geometryObject->position().x < 0.f)
		return new SceneEnd(SceneEnd::QUIT);

	if (input::triggered(input::NEW_SCENE))
		return new Scene::SceneEnd(SceneEnd::NEW_SCENE);

	return nullptr;
}

void GameScene::render(int width, int height) {
	multipleRenderTargets->bindForWriting();

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->use();

	// Texture unit 0 is for base images.
	glUniform1i(shaderProgram->uniformLocation("baseImage"), 0);
	// Texture unit 1 is for normal map.
	glUniform1i(shaderProgram->uniformLocation("normalMap"), 1);
	// Texture unit 0 is for specular map.
	glUniform1i(shaderProgram->uniformLocation("specularMap"), 2);

	glBindVertexArray(geometryObject->geometry()->vertexArray());

	// Base image texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse->textureID());

	// Normal map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normal->textureID());

	// Specular map
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, specular->textureID());

	// Model matrix, unique for each model.
	glm::mat4 model = geometryObject->modelMatrix();

	// Send the matrices to the shader.
	glm::mat4 view = player->camera()->view();
	glm::mat4 MV = view * model;
	glm::mat4 N = glm::transpose(glm::inverse(MV));

	glUniformMatrix4fv(shaderProgram->uniformLocation("modelViewMatrix"), 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix3fv(shaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(N)[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);

	// Draw the triangles
	glDrawElements(GL_TRIANGLES, geometryObject->geometry()->indexCount(), GL_UNSIGNED_INT, (void*)0);

	multipleRenderTargets->render(player->camera(), width, height);

	particleSystem->render(width, height, player->camera());
}