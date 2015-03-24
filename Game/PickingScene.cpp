#include "PickingScene.h"

#include "FrameBufferObjects.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "GeometryObject.h"
#include <AABB.h>
#include "Player.h"

#include <Ray.h>
#include <Triangle.h>

#include "Square.h"
#include "Texture2D.h"
#include "input.h"
#include "settings.h"
#include "Model.h"
#include "Camera.h"

#include <Frustum.h>
#include <Rectangle2D.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

PickingScene::PickingScene() {
	diffuse = new Texture2D("Resources/Models/rock01/diffuse.tga");
	normal = new Texture2D("Resources/Models/rock01/normal.tga");
	specular = new Texture2D("Resources/Models/rock01/specular.tga");

	vertexShader = new Shader("default_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("default_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("picking_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	deferredVertexShader = new Shader("deferred_vertex.glsl", GL_VERTEX_SHADER);
	deferredFragmentShader = new Shader("deferred_fragment.glsl", GL_FRAGMENT_SHADER);
	deferredShaderProgram = new ShaderProgram({ deferredVertexShader, deferredFragmentShader });

	geometry = new Model("Resources/Models/Rock.bin");
	geometry->createAabb();
	aabb = geometry->aabb;
	Rectangle2D rect(glm::vec2(0.f, 0.f), glm::vec2(40.0f, 40.0f));
	quadTree = new QuadTree(rect, 40.f, 4);

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

		//Store in mutliGeometry in order to ensure clean garbage collection
		multiGeometry.push_back(tempGeometry);
		
		quadTree->addObject(tempGeometry, tempRectangle);
	}

	player = new Player();
	player->setMovementSpeed(2.0f);

	multipleRenderTargets = new FrameBufferObjects(deferredShaderProgram, settings::displayWidth(), settings::displayHeight());
}

PickingScene::~PickingScene() {
	delete diffuse;
	delete normal;
	delete specular;

	delete multipleRenderTargets;
	delete deferredShaderProgram;
	delete shaderProgram;

	delete deferredVertexShader;
	delete deferredFragmentShader;

	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	delete quadTree;
	for (GeometryObject* obj : multiGeometry)
		delete obj;
	multiGeometry.clear();

	delete geometry;
	delete player;
}

Scene::SceneEnd* PickingScene::update(double time) {
	player->update(time);

	return nullptr;
}

void PickingScene::render(int width, int height) {
	multipleRenderTargets->bindForWriting();

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->use();

	// Send the matrices to the shader (Per render call operations).
	glm::mat4 view = player->camera()->view();
	glm::mat4 proj = player->camera()->projection(width, height);

	//create mouse ray (Viewport X and Y)
	float x = static_cast<float>(input::cursorX());
	float y = static_cast<float>(input::cursorY());
	
	//Get NDC x and y
	float vx = ((2.0f * x) / width) - 1.0f;
	float vy = 1.0f - ((2.0f * y) / height);
	glm::mat4 inverseView = glm::inverse(view);
	glm::mat4 inverseProj = glm::inverse(proj);
	
	//Ray in clip space
	glm::vec4 rayClip(vx, vy, -1.0f, 0.0f);
	
	//Ray in view space
	glm::vec4 rayEye = inverseProj*rayClip;
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);
	//Per object ray operations continued inside per object loop.

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

	glUniformMatrix4fv(shaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);

	// Light information.
	glm::vec4 lightPosition = view * glm::vec4(-5.f, 0.f, 5.f, 1.f);
	glm::vec3 lightIntensity(1.f, 1.f, 1.f);
	glm::vec3 diffuseKoefficient(1.f, 1.f, 1.f);
	glUniform4fv(shaderProgram->uniformLocation("lightPosition"), 1, &lightPosition[0]);
	glUniform3fv(shaderProgram->uniformLocation("lightIntensity"), 1, &lightIntensity[0]);
	glUniform3fv(shaderProgram->uniformLocation("diffuseKoefficient"), 1, &diffuseKoefficient[0]);
	
	//Cull objects against quadtree
	Frustum* frustum = new Frustum(player->camera()->projection(width, height) * player->camera()->view());
	quadTree->getObjects(*frustum, geometryMap);
	delete frustum;

	// Intersection loop
	float closestDistance = std::numeric_limits<float>::max();
	GeometryObject* closestObjectHit = nullptr;
	for (auto iterator : geometryMap) {
		// Model matrix, unique for each model.
		glm::mat4 model = iterator.second->modelMatrix();

		//Cull still not visible objects
		frustum = new Frustum(player->camera()->projection(width, height) * player->camera()->view() * model);
		if (frustum->collide(geometry->aabb)) {
			// Matrices for each model
			glm::mat4 MV = view * model;
			glm::mat4 N = glm::transpose(glm::inverse(MV));

			// Ray in world space
			glm::vec4 rayOrigin(0.0f, 0.0f, 0.0f, 1.0f);
			rayOrigin = inverseView * rayOrigin;
			glm::vec4 rayWor = glm::vec4(inverseView * rayEye);

			// Ray in local space
			glm::mat4 inverseModel = glm::inverse(model);
			rayOrigin = inverseModel * rayOrigin;
			glm::vec3 rayMod = glm::vec3(inverseModel * rayWor);
			rayMod = glm::normalize(rayMod);
			Ray ray(glm::vec3(rayOrigin), rayMod);

			// Search for hits.
			float distanceToBox = ray.intersect(aabb);
			if (distanceToBox >= 0.f) {
				// If the distance to the box exceeds the distance to the closest triangle, 
				// there is no way that any triangle contained inside that box will 
				// be closer to the viewer.
				if (distanceToBox < closestDistance) {
					for (unsigned int y = 0; (y < geometry->indexCount()); y += 3) {
						unsigned int ind1 = geometry->indices()[y];
						unsigned int ind2 = geometry->indices()[y + 1];
						unsigned int ind3 = geometry->indices()[y + 2];

						Triangle triangle;
						triangle.v1 = geometry->vertices()[ind1].position;
						triangle.v2 = geometry->vertices()[ind2].position;
						triangle.v3 = geometry->vertices()[ind3].position;

						float distanceToTriangle = ray.intersect(triangle);
						if ((distanceToTriangle > 0.f) && (distanceToTriangle < closestDistance)) {
							closestDistance = distanceToTriangle;
							closestObjectHit = iterator.second;
						}
					}
				}
			}
		}
		delete frustum;
	}

	glBindVertexArray(geometry->vertexArray());
	// Drawing loop
	for (auto iterator : geometryMap) {
		// Pass hit to shader
		if (iterator.second == closestObjectHit)
			glUniform1i(shaderProgram->uniformLocation("isHit"), 1);
		else
			glUniform1i(shaderProgram->uniformLocation("isHit"), 0);

		// Model matrix, unique for each model.
		glm::mat4 model = iterator.second->modelMatrix();

		glm::mat4 MV = view * model;
		glm::mat4 N = glm::transpose(glm::inverse(MV));

		glUniformMatrix4fv(shaderProgram->uniformLocation("modelViewMatrix"), 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix3fv(shaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(N)[0][0]);

		glDrawElements(GL_TRIANGLES, geometry->indexCount(), GL_UNSIGNED_INT, (void*)0);
	}
	geometryMap.clear();

	multipleRenderTargets->render(player->camera(), width, height);
}