#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW/glfw3.h>

#include "TerrainScene.h"
#include "SoundSystem.h"

#include "Terrain.h"
#include "Texture2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

TerrainScene::TerrainScene() {
	blendMap = new Texture2D("Resources/Textures/blendmap.tga");
	grassTexture = new Texture2D("Resources/Textures/CGTextures/grass.tga");
	cliffTexture = new Texture2D("Resources/Textures/CGTextures/cliff.tga");
	sandTexture = new Texture2D("Resources/Textures/CGTextures/sand.tga");
	snowTexture = new Texture2D("Resources/Textures/CGTextures/snow.tga");

	skyboxTexture = new CubeMapTexture(
		"Resources/Textures/TropicalSunnyDay/Right.tga",
		"Resources/Textures/TropicalSunnyDay/Left.tga", 
		"Resources/Textures/TropicalSunnyDay/Up.tga", 
		"Resources/Textures/TropicalSunnyDay/Down.tga", 
		"Resources/Textures/TropicalSunnyDay/Back.tga", 
		"Resources/Textures/TropicalSunnyDay/Front.tga" );

	vertexShader = new Shader("default_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("default_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("blendmap_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	// Set texture locations.
	shaderProgram->use();
	glUniform1i(shaderProgram->uniformLocation("blendMap"), 0);
	glUniform1i(shaderProgram->uniformLocation("redTexture"), 1);
	glUniform1i(shaderProgram->uniformLocation("greenTexture"), 2);
	glUniform1i(shaderProgram->uniformLocation("blueTexture"), 3);
	glUniform1i(shaderProgram->uniformLocation("alphaTexture"), 4);

	geometry = new Terrain("Resources/HeightMaps/TestMapSmall.tga");
	geometry->setPosition(0.f, -5.f, 0.f);
	geometry->setScale(50.f, 10.f, 50.f);
	bindTriangleData();

	skybox = new Skybox(skyboxTexture);

	player = new Player();
	player->setMovementSpeed(5.0f);
}

TerrainScene::~TerrainScene() {
	delete blendMap;
	delete grassTexture;
	delete cliffTexture;
	delete sandTexture;
	delete snowTexture;
	
	delete shaderProgram;
	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);

	delete geometry;
	delete player;
	delete skybox;
	delete skyboxTexture;
}

Scene::SceneEnd* TerrainScene::update(double time) {
	player->update(time);
	glm::vec3 position = player->camera()->position();
	player->camera()->setPosition(position.x, dynamic_cast<Terrain*>(geometry)->getY(position.x, position.z) + 2.f, position.z);

	SoundSystem::getInstance()->listener()->setPosition(player->camera()->position());
	SoundSystem::getInstance()->listener()->setOrientation(player->camera()->forward(), player->camera()->up());

	return nullptr;
}

void TerrainScene::render(int width, int height) {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->use();

	// Blend map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, blendMap->textureID());

	// Textures
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, grassTexture->textureID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, cliffTexture->textureID());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, sandTexture->textureID());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, snowTexture->textureID());

	// Model matrix, unique for each model.
	glm::mat4 model = geometry->modelMatrix();

	// Send the matrices to the shader.
	glm::mat4 view = player->camera()->view();
	glm::mat4 MV = view * model;
	glm::mat4 N = glm::transpose(glm::inverse(MV));

	glUniformMatrix4fv(shaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("viewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix3fv(shaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(N)[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);

	// Light information.
	glm::vec4 lightPosition = view * glm::vec4(0.f, 5.f, 0.f, 1.f);
	glm::vec3 lightIntensity(1.f, 1.f, 1.f);
	glm::vec3 diffuseKoefficient(1.f, 1.f, 1.f);

	glUniform4fv(shaderProgram->uniformLocation("lightPosition"), 1, &lightPosition[0]);
	glUniform3fv(shaderProgram->uniformLocation("lightIntensity"), 1, &lightIntensity[0]);
	glUniform3fv(shaderProgram->uniformLocation("diffuseKoefficient"), 1, &diffuseKoefficient[0]);

	glBindVertexArray(vertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	// Draw the triangles
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);

	skybox->render(width, height, player->camera());
}

void TerrainScene::bindTriangleData() {
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
	glEnableVertexAttribArray(2);

	GLuint vertexPos = shaderProgram->attributeLocation("vertex_position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(0));

	GLuint vertexNormal = shaderProgram->attributeLocation("vertex_normal");
	glVertexAttribPointer(vertexNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float) * 3));

	GLuint vertexTexture = shaderProgram->attributeLocation("vertex_texture");
	glVertexAttribPointer(vertexTexture, 2, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float) * 6));

	// Index buffer
	indexCount = geometry->indexCount();
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), geometry->indices(), GL_STATIC_DRAW);
}