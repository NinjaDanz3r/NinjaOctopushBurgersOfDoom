#include "DefRenderTestScene.h"

#include <gl/glew.h>

#include <Texture2D.h>
#include "settings.h"

#include <Shader.h>
#include <ShaderProgram.h>

#include "Player.h"
#include "Camera.h"
#include <Geometry.h>
#include "GeometryObject.h"
#include "Square.h"
#include "Cube.h"
#include "ShadowMap.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

DefRenderTestScene::DefRenderTestScene() {
	texture = new Texture2D("Resources/Textures/kaleido.tga");

	shadowVertexShader = new Shader("shadow_vertex.glsl", GL_VERTEX_SHADER);
	shadowFragmentShader = new Shader("shadow_fragment.glsl", GL_FRAGMENT_SHADER);
	shadowGeometryShader = new Shader("shadow_geometry.glsl", GL_GEOMETRY_SHADER);
	shadowShaderProgram = new ShaderProgram({ shadowVertexShader, shadowGeometryShader, shadowFragmentShader });

	vertexShader = new Shader("default_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("default_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("default_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	deferredVertexShader = new Shader("deferred_vertex.glsl", GL_VERTEX_SHADER);
	deferredFragmentShader = new Shader("deferred_fragment.glsl", GL_FRAGMENT_SHADER);
	deferredShaderProgram = new ShaderProgram({ deferredVertexShader, deferredFragmentShader });

	geometry = new Cube();
	geometryObject = new GeometryObject(geometry);
	geometryGround = new GeometryObject(geometry);
	geometryObject->move(glm::vec3(0.f, 0.005f, -1.f));
	geometryGround->setScale(5.0, 5.0, 5.0);
	geometryGround->setPosition(0.5, -3.0, -2.0);

	player = new Player();
	player->setMovementSpeed(2.0f);

	multipleRenderTargets = new FrameBufferObjects(deferredShaderProgram, settings::displayWidth(), settings::displayHeight());

	shadowMap = new ShadowMap(settings::displayWidth(), settings::displayHeight());
}

DefRenderTestScene::~DefRenderTestScene() {
	delete texture;

	delete multipleRenderTargets;
	delete shadowMap;

	delete deferredShaderProgram;
	delete shadowShaderProgram;
	delete shaderProgram;

	delete shadowVertexShader;
	delete shadowGeometryShader;
	delete shadowFragmentShader;
	
	delete deferredVertexShader;
	delete deferredFragmentShader;

	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	delete geometryObject;
	delete geometryGround;
	delete geometry;
	delete player;
}

Scene::SceneEnd* DefRenderTestScene::update(double time) {
	player->update(time);

	shadowTime += time;
	multipleRenderTargets->light.position = glm::vec4(5.f * sin(shadowTime), 3.f, 3.f + 5.f * cos(shadowTime), 1.f);

	return nullptr;
}

void DefRenderTestScene::render(int width, int height) {
	multipleRenderTargets->bindForWriting();

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->use();

	// Texture unit 0 is for base images.
	glUniform1i(shaderProgram->uniformLocation("baseImage"), 0);

	glBindVertexArray(geometryObject->geometry()->vertexArray());

	// Base image texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());

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

	// Model matrix, unique for each model.
	model = geometryGround->modelMatrix();
	glUniformMatrix4fv(shaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);

	// Draw the triangles
	glDrawElements(GL_TRIANGLES, geometryObject->geometry()->indexCount(), GL_UNSIGNED_INT, (void*)0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Geometry rendering complete.

	renderShadows(width, height);
	//Shadow map rendering complete.

	multipleRenderTargets->render(player->camera(), width, height);
	//Lighting render pass complete.
}

void DefRenderTestScene::renderShadows(int width, int height) {
	shadowMap->bindForWriting();
	shadowShaderProgram->use();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(geometryObject->geometry()->vertexArray());

	// Model matrix, unique for each model.
	glm::mat4 model = geometryObject->modelMatrix();
	glm::vec3 position = glm::vec3(multipleRenderTargets->light.position);

	// Send the matrices to the shader.
	glm::mat4 viewMatrix = glm::lookAt(position, geometryObject->position(), glm::vec3(0, 1, 0));
	glm::mat4 perspectiveMatrix = glm::perspective(45.0f, 1.0f, 2.0f, 50.0f);
	glm::mat4 modelView = viewMatrix * model;
	glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelView));

	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightModelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightViewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightProjectionMatrix"), 1, GL_FALSE, &perspectiveMatrix[0][0]);
	glUniformMatrix3fv(shadowShaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(normalMatrix)[0][0]);

	// Draw the triangles
	glDrawElements(GL_TRIANGLES, geometryObject->geometry()->indexCount(), GL_UNSIGNED_INT, (void*)0);

	// Model matrix, unique for each model.
	model = geometryGround->modelMatrix();
	modelView = viewMatrix * model;
	normalMatrix = glm::transpose(glm::inverse(modelView));

	glUniformMatrix3fv(shadowShaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(normalMatrix)[0][0]);
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightModelMatrix"), 1, GL_FALSE, &model[0][0]);

	// Draw the triangles
	glDrawElements(GL_TRIANGLES, geometryObject->geometry()->indexCount(), GL_UNSIGNED_INT, (void*)0);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//shadow map render call complete.
	//Now Bind uniform for sampling the shadow map in lighting pass.

	deferredShaderProgram->use();
	glm::mat4 uVTransformMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);
	// Send the matrices to the shader.
	glm::mat4 view = player->camera()->view();
	glm::mat4 viewInverse = glm::inverse(view);

	glUniformMatrix4fv(deferredShaderProgram->uniformLocation("lightViewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(deferredShaderProgram->uniformLocation("lightProjectionMatrix"), 1, GL_FALSE, &perspectiveMatrix[0][0]);
	glUniformMatrix4fv(deferredShaderProgram->uniformLocation("inverseViewMatrix"), 1, GL_FALSE, &viewInverse[0][0]);
	glUniformMatrix4fv(deferredShaderProgram->uniformLocation("UVtransformMatrix"), 1, GL_FALSE, &uVTransformMatrix[0][0]);

	glUniform1i(deferredShaderProgram->uniformLocation("tShadowMap"), FrameBufferObjects::NUM_TEXTURES + 1);
	shadowMap->bindForReading(GL_TEXTURE0 + FrameBufferObjects::NUM_TEXTURES + 1);
}