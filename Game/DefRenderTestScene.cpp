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
#include "ShadowMapping.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

DefRenderTestScene::DefRenderTestScene() {
	state = 0;

	texture = new Texture2D("Resources/Textures/kaleido.tga");

	shadowVertexShader = new Shader("shadow_vertex.glsl", GL_VERTEX_SHADER);
	shadowFragmentShader = new Shader("shadow_fragment.glsl", GL_FRAGMENT_SHADER);
	shadowShaderProgram = new ShaderProgram({ shadowVertexShader, shadowFragmentShader });

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
	geometryGround->setScale(5.0, 5.0, 5.0);
	geometryGround->setPosition(0.5, -3.0, -2.0);

	player = new Player();
	player->setMovementSpeed(2.0f);

	multipleRenderTargets = new FrameBufferObjects(deferredShaderProgram, settings::displayWidth(), settings::displayHeight());

	shadowMap = new ShadowMapping();
	shadowMap->begin(settings::displayWidth(), settings::displayHeight());
}

DefRenderTestScene::~DefRenderTestScene() {
	delete texture;

	delete multipleRenderTargets;
	delete shadowMap;

	delete deferredShaderProgram;
	delete shadowShaderProgram;
	delete shaderProgram;

	delete shadowVertexShader;
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

	return nullptr;
}

void DefRenderTestScene::render(int width, int height) {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shadowShaderProgram->use();

	glBindVertexArray(geometryObject->geometry()->vertexArray());

	// Model matrix, unique for each model.
	glm::mat4 model = geometryObject->modelMatrix();
	glm::vec3 position = glm::vec3(0.f, 3.f, 3.f);

	// Send the matrices to the shader.
	glm::mat4 viewMatrix = glm::lookAt(position, geometryObject->position(), glm::vec3(0, 1, 0));
	glm::mat4 perspectiveMatrix = glm::perspective(45.0f, 1.0f, 2.0f, 50.0f);

	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightModelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightViewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightProjectionMatrix"), 1, GL_FALSE, &perspectiveMatrix[0][0]);

	// Draw the triangles
	glDrawElements(GL_TRIANGLES, geometryObject->geometry()->indexCount(), GL_UNSIGNED_INT, (void*)0);

	// Model matrix, unique for each model.
	model = geometryGround->modelMatrix();
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightModelMatrix"), 1, GL_FALSE, &model[0][0]);
	
	// Draw the triangles
	glDrawElements(GL_TRIANGLES, geometryObject->geometry()->indexCount(), GL_UNSIGNED_INT, (void*)0);
}

/*DefRenderTestScene::~DefRenderTestScene() {
	delete texture;

	delete multiplerendertargets;
	delete deferredShaderProgram;
	delete shaderProgram;

	delete deferredVertexShader;
	delete deferredFragmentShader;

	delete shadowShaderProgram;
	delete shadowVertexShader;
	delete shadowFragmentShader;

	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	delete geometry;
	delete player;
}

Scene::SceneEnd* DefRenderTestScene::update(double time) {
	player->update(time);
	//geometry->rotate(1, 1, 1);
	return nullptr;
}

void DefRenderTestScene::render(int width, int height) {
	shadowShaderProgram->use();
	//multiplerendertargets->bindForWriting();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_BLEND);

	glViewport(0, 0, width, height);
	
	//bindGeometry(width,height,geometry);
	// Model matrix, unique for each model.
	glm::mat4 model = geometryObject->modelMatrix();

	glUniformMatrix4fv(shaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);

	//shadowMap->bindForWriting();
	//glDrawBuffer(GL_NONE);
	//shadowRender(width, height);

	shaderProgram->use();	
	glBindVertexArray(gVertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);

	multiplerendertargets->bindForWriting();
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
	//Render ground

	bindGeometry(width, height,geometryGround);	
	glBindVertexArray(groundVertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);

	glDisable(GL_DEPTH_TEST);

	if (state == 1)
	{
		showTex(width, height);
	}
	else if (state == 0)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		deferredRender(width, height);
	}
	
}

void DefRenderTestScene::deferredRender(int width, int height){
	deferredShaderProgram->use();

	//Blending enabled for handling multiple light sources
	//glEnable(GL_BLEND);
	//glBlendEquation(GL_FUNC_ADD);
	//glBlendFunc(GL_ONE, GL_ONE);

	shadowMap->bindForReading(GL_TEXTURE3);
	//bindLighting(width, height);
	multiplerendertargets->bindForReading();


	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(qVertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, qIndexBuffer);

	glDrawElements(GL_TRIANGLES, qIndexCount, GL_UNSIGNED_INT, (void*)0);
}

void DefRenderTestScene::shadowRender(int width, int height){
	glBindVertexArray(shadowVertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shadowIndexBuffer);

	glClear(GL_DEPTH_BUFFER_BIT);

	// Model matrix, unique for each model.
	glm::mat4 model = geometryObject->modelMatrix();
	glm::vec3 position = glm::vec3(0.f, 3.f, 3.f);

	// Send the matrices to the shader.
	glm::mat4 viewMatrix = glm::lookAt(position, geometryObject->position(), glm::vec3(0, 1, 0));
	glm::mat4 perspectiveMatrix = glm::perspective(45.0f, 1.0f, 2.0f, 50.0f);

	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightmodelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightViewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightProjectionMatrix"), 1, GL_FALSE, &perspectiveMatrix[0][0]);

	//Render main geometry 
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
*/