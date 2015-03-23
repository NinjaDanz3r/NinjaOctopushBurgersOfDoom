#include "MorphScene.h"
#include <gl/glew.h>
#include <gl/GL.h>

#include "FrameBufferObjects.h"

#include <Model.h>
#include "GeometryObject.h"
#include <Texture2D.h>

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

MorphScene::MorphScene() {
	state = 0;

	diffuse = new Texture2D("Resources/Models/rock01/diffuse.tga");
	normal = new Texture2D("Resources/Models/rock01/normal.tga");
	specular = new Texture2D("Resources/Models/rock01/specular.tga");

	vertexShader = new Shader("morph_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("default_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("normalspecularmap_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	deferredVertexShader = new Shader("deferred_vertex.glsl", GL_VERTEX_SHADER);
	deferredFragmentShader = new Shader("deferred_fragment.glsl", GL_FRAGMENT_SHADER);
	deferredShaderProgram = new ShaderProgram({ deferredVertexShader, deferredFragmentShader });

	geometry = new Model("Resources/Models/Rock.bin");

	geometryObject = new GeometryObject(geometry);
	geometryObject->setScale(0.01f, 0.01f, 0.01f);

	targetPositions = new glm::vec3[geometryObject->geometry()->vertexCount()];
	glm::mat4 targetScaleRotation = glm::scale(glm::vec3(0.1f, 0.1f, 0.1f))*glm::rotate(90.f, glm::vec3(0.f, 1.f, 0.f));

	//Create target positions for lerping
	for (unsigned int i = 0; i < geometryObject->geometry()->vertexCount(); i++) {
		targetPositions[i] = glm::vec3(targetScaleRotation*glm::vec4(geometryObject->geometry()->vertices()[i].position, 1.f));
	}

	GLuint targetBuffer;
	// Generate target buffer
	glGenBuffers(1, &targetBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, targetBuffer);
	glBufferData(GL_ARRAY_BUFFER, geometryObject->geometry()->vertexCount() * sizeof(glm::vec3), targetPositions, GL_STATIC_DRAW);

	// Target vertex layout (adds to geometry objects current layout)
	glBindVertexArray(geometryObject->geometry()->vertexArray());
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glBindVertexArray(0);
	direction = true;
	t = 0;
	player = new Player();
	player->setMovementSpeed(2.0f);
	multipleRenderTargets = new FrameBufferObjects(deferredShaderProgram, settings::displayWidth(), settings::displayHeight());
}

MorphScene::~MorphScene() {
	delete diffuse;
	delete normal;
	delete specular;

	delete multipleRenderTargets;
	delete deferredShaderProgram;
	delete shaderProgram;

	delete deferredVertexShader;
	delete deferredFragmentShader;
	delete[] targetPositions;

	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	delete geometryObject;
	delete geometry;
	delete player;
}

Scene::SceneEnd* MorphScene::update(double time) {
	player->update(time);

	if (input::triggered(input::CHANGE_RENDER_STATE))
		state = !state;

	if (direction == true) {
		if (t < 1.f)
			t += 0.3f * static_cast<float>(time);
		else
			direction = false;
	} else if (direction == false){
		if (t > 0.f)
			t -= 0.3f * static_cast<float>(time);
		else
			direction = true;
	}

	return nullptr;
}

void MorphScene::render(int width, int height) {
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

	glBindVertexArray(geometryObject->geometry()->vertexArray());

	//T value, used for interpolation
	glUniform1f(shaderProgram->uniformLocation("tValue"), t);

	// Base image texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse->textureID());

	// Normal map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normal->textureID());

	// Specular map
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, specular->textureID());

	// Model matrix, unique for each model.
	glm::mat4 model = geometryObject->modelMatrix();

	// Send the matrices to the shader.
	glm::mat4 view = player->camera()->view();
	glm::mat4 MV = view * model;
	glm::mat4 N = glm::transpose(glm::inverse(MV));

	glUniformMatrix4fv(shaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("viewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix3fv(shaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(N)[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);

	// Draw the triangles
	glDrawElements(GL_TRIANGLES, geometryObject->geometry()->indexCount(), GL_UNSIGNED_INT, (void*)0);

	if (state == 1) {
		multipleRenderTargets->showTextures(width, height);
	} else if (state == 0) {
		multipleRenderTargets->render(player->camera(), width, height);
	}
}