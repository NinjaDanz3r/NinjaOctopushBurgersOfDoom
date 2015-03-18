#include "TerrainScene.h"
#include <gl/glew.h>
#include <gl/GL.h>

#include "FrameBufferObjects.h"
#include "SoundSystem.h"
#include "Listener.h"

#include "Terrain.h"
#include "TerrainObject.h"
#include "Skybox.h"
#include <Texture2D.h>
#include "CubeMapTexture.h"

#include "settings.h"
#include "input.h"

#include <Shader.h>
#include <ShaderProgram.h>
#include "Camera.h"
#include "Player.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

TerrainScene::TerrainScene() {
	state = 0;

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

	deferredVertexShader = new Shader("deferred_vertex.glsl", GL_VERTEX_SHADER);
	deferredFragmentShader = new Shader("deferred_fragment.glsl", GL_FRAGMENT_SHADER);
	deferredShaderProgram = new ShaderProgram({ deferredVertexShader, deferredFragmentShader });

	// Set texture locations.
	shaderProgram->use();
	glUniform1i(shaderProgram->uniformLocation("blendMap"), 0);
	glUniform1i(shaderProgram->uniformLocation("redTexture"), 1);
	glUniform1i(shaderProgram->uniformLocation("greenTexture"), 2);
	glUniform1i(shaderProgram->uniformLocation("blueTexture"), 3);
	glUniform1i(shaderProgram->uniformLocation("alphaTexture"), 4);

	terrain = new Terrain("Resources/HeightMaps/TestMapSmall.tga");
	terrainObject = new TerrainObject(terrain);
	terrainObject->setPosition(0.f, -5.f, 0.f);
	terrainObject->setScale(50.f, 10.f, 50.f);
	terrain->setTextureRepeat(glm::vec2(10.f, 10.f));

	skybox = new Skybox(skyboxTexture);

	player = new Player();
	player->setMovementSpeed(5.0f);
	multipleRenderTargets = new FrameBufferObjects(deferredShaderProgram, settings::displayWidth(), settings::displayHeight());
}

TerrainScene::~TerrainScene() {
	delete blendMap;
	delete grassTexture;
	delete cliffTexture;
	delete sandTexture;
	delete snowTexture;
	
	delete multipleRenderTargets;
	delete deferredShaderProgram;
	delete shaderProgram;

	delete deferredVertexShader;
	delete deferredFragmentShader;

	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	delete terrainObject;
	delete terrain;
	delete player;
	delete skybox;
	delete skyboxTexture;
}

Scene::SceneEnd* TerrainScene::update(double time) {
	player->update(time);
	glm::vec3 position = player->camera()->position();
	player->camera()->setPosition(position.x, terrainObject->getY(position.x, position.z) + 2.f, position.z);

	SoundSystem::getInstance()->listener()->setPosition(player->camera()->position());
	SoundSystem::getInstance()->listener()->setOrientation(player->camera()->forward(), player->camera()->up());

	if (input::triggered(input::CHANGE_RENDER_STATE))
		state = !state;

	return nullptr;
}

void TerrainScene::render(int width, int height) {
	multipleRenderTargets->bindForWriting();

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

	// Texture repeat
	glUniform2fv(shaderProgram->uniformLocation("textureRepeat"), 1, &terrain->textureRepeat()[0]);

	// Model matrix, unique for each model.
	glm::mat4 model = terrainObject->modelMatrix();

	// Send the matrices to the shader.
	glm::mat4 view = player->camera()->view();
	glm::mat4 MV = view * model;
	glm::mat4 N = glm::transpose(glm::inverse(MV));

	glUniformMatrix4fv(shaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("viewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix3fv(shaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(N)[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);

	glBindVertexArray(terrainObject->geometry()->vertexArray());

	// Draw the triangles
	glDrawElements(GL_TRIANGLES, terrainObject->geometry()->indexCount(), GL_UNSIGNED_INT, (void*)0);

	if (state == 1) {
		multipleRenderTargets->showTextures(width, height);
	} else if (state == 0) {
		multipleRenderTargets->render(player->camera(), width, height);
		skybox->render(width, height, player->camera());
	}
}