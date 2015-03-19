#include "FrustumScene.h"

#include <gl/glew.h>
#include <string>

#include "Square.h"
#include "Texture2D.h"
#include "input.h"
#include "Model.h"
#include "settings.h"
#include "Camera.h"

#include "Shader.h"
#include "ShaderProgram.h"
#include "GeometryObject.h"
#include "Player.h"
#include "FrameBufferObjects.h"
#include "Datastructures.h"
#include "Game.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

std::string Game::additionalData;

FrustumScene::FrustumScene() {
	state = 0;

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

	geometry = new Model("Resources/Models/Rock.bin");
	geometry->createAabb();
	Rectangle2D rect(glm::vec2(0.f, 0.f), glm::vec2(40.0f, 40.0f));
	qTree = new QuadTree(rect, 0, 3); 
	int modelsInTree = 0;
	for (int i = 0; i < numModels; i++){
		GeometryObject* tempGeometry = new GeometryObject(geometry);
		tempGeometry->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
		int rand1 = rand() % 41 - 20;
		int rand2 = rand() % 41 - 20;
		int rand3 = rand() % 41 - 20;
		tempGeometry->setPosition(glm::vec3((float)rand1, (float)rand2, (float)rand3));
		rand1 = rand() % 361;
		rand2 = rand() % 361;
		rand3 = rand() % 361;
		tempGeometry->setRotation((float)rand1, (float)rand2, (float)rand3);

		Rectangle2D tempRectangle = Rectangle2D(*tempGeometry->geometry(), tempGeometry->modelMatrix());
		multiGeometry.push_back(tempGeometry);
		
		if (qTree->addObject(tempGeometry, tempRectangle))
			modelsInTree++;
		else
			delete tempGeometry;
	}

	player = new Player();
	player->setMovementSpeed(2.0f);

	multipleRenderTargets = new FrameBufferObjects(deferredShaderProgram, settings::displayWidth(), settings::displayHeight());
}

FrustumScene::~FrustumScene() {
	delete diffuse;
	delete normal;
	delete specular;

	delete shaderProgram;
	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	delete multipleRenderTargets;
	delete deferredShaderProgram;
	delete deferredVertexShader;
	delete deferredFragmentShader;

	delete qTree;
	for (GeometryObject* obj : multiGeometry)
		delete obj;
	multiGeometry.clear();

	delete geometry;
	delete player;
}

Scene::SceneEnd* FrustumScene::update(double time) {
	player->update(time);

	if (input::triggered(input::CHANGE_RENDER_STATE))
		state = !state;

	return nullptr;
}

void FrustumScene::render(int width, int height) {
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

	// Base image texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse->textureID());

	// Normal map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normal->textureID());

	// Specular map
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, specular->textureID());

	// Send the matrices to the shader.
	glm::mat4 view = player->camera()->view();

	glUniformMatrix4fv(shaderProgram->uniformLocation("viewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);
	glBindVertexArray(geometry->vertexArray());
	// Drawing loop
	int objectsRendered = 0;
	frustum = new Frustum(player->camera()->projection(width, height) * player->camera()->view());
	qTree->getObjects(*frustum, geometryMap);
	typedef std::map<GeometryObject*, GeometryObject*>::iterator it_type;
	for (it_type iterator = geometryMap.begin(); iterator != geometryMap.end(); iterator++) {
		objectsRendered++;
		// Model matrix, unique for each model.
		glm::mat4 model = iterator->second->modelMatrix();

		glm::mat4 MV = view * model;
		glm::mat4 N = glm::transpose(glm::inverse(MV));

		glUniformMatrix4fv(shaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix3fv(shaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(N)[0][0]);

		glDrawElements(GL_TRIANGLES, geometry->indexCount(), GL_UNSIGNED_INT, (void*)0);
	}
	Game::additionalData = std::to_string(objectsRendered);
	geometryMap.clear();

	//Frustum culling against AABB's
	//for (int i = 0; i < numModels; i++)
	//{
	//	glm::mat4 model = multiGeometry[i]->modelMatrix();
	//	frustum = new Frustum(player->camera()->projection(width, height)[0][0] * player->camera()->view() * glm::inverse(model));
	//	if (frustum->collide(geometry->aabb))
	//	{
	//		objectsRendered++;

	//		glm::mat4 MV = view * model;
	//		glm::mat4 N = glm::transpose(glm::inverse(MV));

	//		glUniformMatrix4fv(shaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);
	//		glUniformMatrix3fv(shaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(N)[0][0]);

	//		glDrawElements(GL_TRIANGLES, geometry->indexCount(), GL_UNSIGNED_INT, (void*)0);
	//	}
	//}

	if (state == 1) {
		multipleRenderTargets->showTextures(width, height);
	}
	else if (state == 0) {
		multipleRenderTargets->render(player->camera(), width, height);
	}
	delete frustum;
}