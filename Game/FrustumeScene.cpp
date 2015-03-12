#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW\glfw3.h>

#include "FrustumScene.h"

#include "Square.h"
#include "Texture2D.h"
#include "input.h"
#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

FrustumScene::FrustumScene() {
	diffuse = new Texture2D("Resources/Models/rock01/diffuse.tga");
	normal = new Texture2D("Resources/Models/rock01/normal.tga");
	specular = new Texture2D("Resources/Models/rock01/specular.tga");

	vertexShader = new Shader("default_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("default_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("default_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	shaderProgram->use();

	// Texture unit 0 is for base images.
	glUniform1i(shaderProgram->uniformLocation("baseImage"), 0);
	// Texture unit 1 is for normal map.
	glUniform1i(shaderProgram->uniformLocation("normalMap"), 1);
	// Texture unit 0 is for specular map.
	glUniform1i(shaderProgram->uniformLocation("specularMap"), 2);

	geometry = new Model("Resources/Models/Rock.bin");

	for (int i = 0; i < numModels; i++){
		GeometryObject* tempGeometry = new GeometryObject(geometry);
		tempGeometry->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
		int rand1 = rand() % 21 - 10;
		int rand2 = rand() % 21 - 10;
		int rand3 = -10 - rand() % 10;
		tempGeometry->setPosition(glm::vec3((float)rand1, (float)rand2, (float)rand3));
		rand1 = rand() % 361;
		rand2 = rand() % 361;
		rand3 = rand() % 361;
		tempGeometry->setRotation((float)rand1, (float)rand2, (float)rand3);
		multiGeometry.push_back(tempGeometry);
	}

	player = new Player();
	player->setMovementSpeed(2.0f);
}

FrustumScene::~FrustumScene() {
	delete diffuse;
	delete normal;
	delete specular;

	delete shaderProgram;
	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	for (int i = 0; i < numModels; i++) {
		delete multiGeometry[i];
	}
	multiGeometry.clear();

	delete geometry;
	delete player;
}

Scene::SceneEnd* FrustumScene::update(double time) {
	player->update(time);

	return nullptr;
}

void FrustumScene::render(int width, int height) {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Send the matrices to the shader (Per render call operations).
	glm::mat4 view = player->camera()->view();
	glm::mat4 proj = player->camera()->projection(width, height);

	// Base image texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse->textureID());

	// Normal map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normal->textureID());

	// Specular map
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, specular->textureID());

	glUniformMatrix4fv(shaderProgram->uniformLocation("viewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);

	// Light information.
	glm::vec4 lightPosition = view * glm::vec4(-5.f, 0.f, 5.f, 1.f);
	glm::vec3 lightIntensity(1.f, 1.f, 1.f);
	glm::vec3 diffuseKoefficient(1.f, 1.f, 1.f);
	glUniform4fv(shaderProgram->uniformLocation("lightPosition"), 1, &lightPosition[0]);
	glUniform3fv(shaderProgram->uniformLocation("lightIntensity"), 1, &lightIntensity[0]);
	glUniform3fv(shaderProgram->uniformLocation("diffuseKoefficient"), 1, &diffuseKoefficient[0]);

	glBindVertexArray(geometry->vertexArray());

	// Drawing loop
	for (int i = 0; i < numModels; i++) {
		// Model matrix, unique for each model.
		glm::mat4 model = multiGeometry[i]->modelMatrix();

		glm::mat4 MV = view * model;
		glm::mat4 N = glm::transpose(glm::inverse(MV));

		glUniformMatrix4fv(shaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix3fv(shaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(N)[0][0]);

		glDrawElements(GL_TRIANGLES, geometry->indexCount(), GL_UNSIGNED_INT, (void*)0);
	}
}