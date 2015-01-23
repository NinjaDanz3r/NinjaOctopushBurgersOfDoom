#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW/glfw3.h>

#include "AudioScene.h"
#include "SoundSystem.h"

#include "Cube.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

AudioScene::AudioScene() {
	texture = new Texture("Resources/Textures/kaleido.tga");
	shaders = new Shaders("default");

	glUseProgram(shaders->shaderProgram());

	// Texture unit 0 is for base images.
	glUniform1i(shaders->baseImageLocation(), 0);

	geometry = new Cube();
	bindTriangleData();

	player = new Player();
	player->setMovementSpeed(2.0f);

	waveFile = new WaveFile("Resources/Audio/Testing.wav");
	buffer = new SoundBuffer(waveFile);
	sound = new Sound(buffer);
	sound->setLooping(true);
	sound->setGain(2.f);
	sound->play();
}

AudioScene::~AudioScene() {
	delete texture;
	delete shaders;
	delete geometry;
	delete player;

	delete sound;
	delete buffer;
	delete waveFile;
}

Scene::SceneEnd* AudioScene::update(double time) {
	player->update(time);

	SoundSystem::getInstance()->listener()->setPosition(player->camera()->position());
	SoundSystem::getInstance()->listener()->setOrientation(player->camera()->forward(), player->camera()->up());

	return nullptr;
}

void AudioScene::render(int width, int height) {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	// Base image texture
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());

	// Model matrix, unique for each model.
	glm::mat4 model = geometry->modelMatrix();

	// Send the matrices to the shader.
	glm::mat4 view = player->camera()->view();
	glm::mat4 MV = view * model;
	glm::mat4 N = glm::transpose(glm::inverse(MV));

	glUniformMatrix4fv(shaders->modelLocation(), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(shaders->viewLocation(), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix3fv(shaders->normalLocation(), 1, GL_FALSE, &glm::mat3(N)[0][0]);
	glUniformMatrix4fv(shaders->projectionLocation(), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);

	// Light information.
	glm::vec4 lightPosition = view * glm::vec4(-5.f, 0.f, 5.f, 1.f);
	glm::vec3 lightIntensity(1.f, 1.f, 1.f);
	glm::vec3 diffuseKoefficient(1.f, 1.f, 1.f);

	glUniform4fv(shaders->lightPositionLocation(), 1, &lightPosition[0]);
	glUniform3fv(shaders->lightIntensityLocation(), 1, &lightIntensity[0]);
	glUniform3fv(shaders->diffuseKoefficientLocation(), 1, &diffuseKoefficient[0]);

	// Draw the triangles
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
}

void AudioScene::bindTriangleData() {
	// Vertex buffer
	vertexCount = geometry->vertexCount();
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Geometry::Vertex), geometry->vertices(), GL_STATIC_DRAW);

	// Define vertex data layout
	glGenVertexArrays(1, &vertexAttribute);
	glBindVertexArray(vertexAttribute);
	glEnableVertexAttribArray(0); //the vertex attribute object will remember its enabled attributes
	glEnableVertexAttribArray(1);

	GLuint vertexPos = glGetAttribLocation(shaders->shaderProgram(), "vertex_position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(0));

	GLuint vertexTexture = glGetAttribLocation(shaders->shaderProgram(), "vertex_texture");
	glVertexAttribPointer(vertexTexture, 2, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float) * 3));

	// Index buffer
	indexCount = geometry->indexCount();
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), geometry->indices(), GL_STATIC_DRAW);
}