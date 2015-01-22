#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW\glfw3.h>

#include "AudioScene.h"
#include "util.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

using namespace std;

AudioScene::AudioScene() {
	texture = new Texture("Resources/Textures/bth_image.tga");
	shaders = new Shaders("default");

	glUseProgram(shaders->shaderProgram());

	// Texture unit 0 is for base images.
	glUniform1i(shaders->baseImageLocation(), 0);

	bthSquare = new BTHSquare();
	bindTriangleData();

	player = new Player();
	player->setMovementSpeed(2.0f);

	// Open default audio device.
	device = alcOpenDevice(nullptr);
	if (!device)
		util::log("Couldn't open default audio device.");

	// Create audio context.
	context = alcCreateContext(device, nullptr);
	if (!alcMakeContextCurrent(context))
		util::log("Couldn't create audio context.");

	// Create audio source.
	alGenSources((ALuint)1, &source);
	
	alSourcef(source, AL_PITCH, 1.f);
	alSourcef(source, AL_GAIN, 1.f);
	alSource3f(source, AL_POSITION, 0.f, 0.f, 0.f);
	alSource3f(source, AL_VELOCITY, 0.f, 0.f, 0.f);
	alSourcei(source, AL_LOOPING, AL_TRUE);

	waveFile = new WaveFile("Resources/Audio/Testing.wav");
	buffer = new SoundBuffer(waveFile);

	ALenum error;
	alSourcei(source, AL_BUFFER, buffer->buffer());
	error = alGetError();
	if (error != AL_NO_ERROR)
		util::log("Couldn't set sound source buffer.");

	alSourcePlay(source);
	error = alGetError();
	if (error != AL_NO_ERROR)
		util::log("Couldn't play sound.");
}

AudioScene::~AudioScene() {
	delete texture;
	delete shaders;
	delete bthSquare;
	delete player;

	alDeleteSources(1, &source);
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);

	delete waveFile;
	delete buffer;
}

Scene::SceneEnd* AudioScene::update(double time) {
	player->update(time);

	return nullptr;
}

void AudioScene::render(int width, int height) {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(gVertexAttribute);

	// Base image texture
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());

	// Model matrix, unique for each model.
	glm::mat4 model = bthSquare->modelMatrix();

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

	// Draw the points from the currently bound VAO with current in-use shader
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void AudioScene::bindTriangleData() {
	vertexCount = bthSquare->count();

	// Create buffer and set data
	glGenBuffers(1, &gVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(BTHSquare::TriangleVertex) * bthSquare->count(), bthSquare->vertexes(), GL_STATIC_DRAW);

	// Define vertex data layout
	glGenVertexArrays(1, &gVertexAttribute);
	glBindVertexArray(gVertexAttribute);
	glEnableVertexAttribArray(0); //the vertex attribute object will remember its enabled attributes
	glEnableVertexAttribArray(1);

	GLuint vertexPos = glGetAttribLocation(shaders->shaderProgram(), "vertex_position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(BTHSquare::TriangleVertex), BUFFER_OFFSET(0));

	GLuint vertexTexture = glGetAttribLocation(shaders->shaderProgram(), "vertex_texture");
	glVertexAttribPointer(vertexTexture, 2, GL_FLOAT, GL_FALSE, sizeof(BTHSquare::TriangleVertex), BUFFER_OFFSET(sizeof(float) * 3));
}