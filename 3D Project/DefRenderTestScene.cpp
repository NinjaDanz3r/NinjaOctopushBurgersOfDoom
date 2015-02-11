#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW\glfw3.h>
#include "DefRenderTestScene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

DefRenderTestScene::DefRenderTestScene() {
	texture = new Texture("Resources/Textures/bth_image.tga");
	shaders = new Shaders("default");

	glUseProgram(shaders->shaderProgram());

	// Texture unit 0 is for base images.
	glUniform1i(shaders->baseImageLocation(), 0);

	testCube = new Cube();
	
	bindTriangleData();
	player = new Player();
	player->setMovementSpeed(10.0f);
	//INKLUDERA WIDTH OCH HEIGHT, initializera nya variabler.
	multiplerendertargets = new FrameBufferObjects(settings::displayWidth(), settings::displayHeight());

	//Stämmer shaders callsen?
	diffuseID = glGetUniformLocationARB(shaders->shaderProgram(), "tDiffuse");
	positionID = glGetUniformLocationARB(shaders->shaderProgram(), "tPosition");
	normalID = glGetUniformLocationARB(shaders->shaderProgram(), "tNormal");
}

DefRenderTestScene::~DefRenderTestScene() {
	delete texture;
	delete shaders;
	delete testCube;
	delete player;
}

Scene::SceneEnd* DefRenderTestScene::update(double time) {
	player->update(time);
	testCube->rotate(1, 2, 1);
	return nullptr;
}

void DefRenderTestScene::render(int width, int height) {
	//Nästa steg fixa render funktion för att reflektera DefferedRender + model render
	//Sen shaders.
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);

	multiplerendertargets->begin();
	//insert Model render here ples--, är redan inne, utgår jag från.
	
	glBindVertexArray(gVertexAttribute);

	// Base image texture
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());

	// Model matrix, unique for each model.
	glm::mat4 model = testCube->modelMatrix();

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
	multiplerendertargets->end();

}

void DefRenderTestScene::bindTriangleData() {
	vertexCount = testCube->count();

	// Create buffer and set data
	glGenBuffers(1, &gVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::TriangleVertex) * testCube->count(), testCube->vertexes(), GL_STATIC_DRAW);

	// Define vertex data layout
	glGenVertexArrays(1, &gVertexAttribute);
	glBindVertexArray(gVertexAttribute);
	glEnableVertexAttribArray(0); //the vertex attribute object will remember its enabled attributes
	glEnableVertexAttribArray(1);

	GLuint vertexPos = glGetAttribLocation(shaders->shaderProgram(), "vertex_position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(Cube::TriangleVertex), BUFFER_OFFSET(0));

	GLuint vertexTexture = glGetAttribLocation(shaders->shaderProgram(), "vertex_texture");
	glVertexAttribPointer(vertexTexture, 2, GL_FLOAT, GL_FALSE, sizeof(Cube::TriangleVertex), BUFFER_OFFSET(sizeof(float)* 3));
}