#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW\glfw3.h>
#include "DefRenderTestScene.h"
#include "Cube.h"
#include "Texture2D.h"
#include "settings.h"
#include "input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

DefRenderTestScene::DefRenderTestScene() {
	texture = new Texture2D("Resources/Textures/kaleido.tga");
	state = 0;

	vertexShader = new Shader("default_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("default_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("deferred_first_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	secondVertexShader = new Shader("deferred_second_vertex.glsl", GL_VERTEX_SHADER);
	secondFragmentShader = new Shader("deferred_second_fragment.glsl", GL_FRAGMENT_SHADER);
	secondShaderProgram = new ShaderProgram({ secondVertexShader, secondFragmentShader });

	player = new Player();
	player->setMovementSpeed(2.0f);
	multipleRenderTargets = new FrameBufferObjects(secondShaderProgram, settings::displayWidth(), settings::displayHeight());

	geometry = new Cube();
	geometryObject = new GeometryObject(geometry);
	shaderProgram->use();
	bindTriangleData();
}

DefRenderTestScene::~DefRenderTestScene() {
	delete texture;

	delete multipleRenderTargets;
	delete secondShaderProgram;
	delete shaderProgram;

	delete secondVertexShader;
	delete secondFragmentShader;

	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);

	delete geometry;
	delete geometryObject;
	delete player;
}

Scene::SceneEnd* DefRenderTestScene::update(double time) {
	player->update(time);
	geometryObject->rotate(4.0f * static_cast<float>(time), 4.0f * static_cast<float>(time), 4.0f * static_cast<float>(time));

	if (input::triggered(input::CHANGE_RENDER_STATE))
		state = !state;

	return nullptr;
}

void DefRenderTestScene::render(int width, int height) {
	shaderProgram->use();
	glUniform1i(shaderProgram->uniformLocation("tDiffuse"), 0);
	multipleRenderTargets->bindForWriting();

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	bindGeometry(width, height);

	glBindVertexArray(vertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);

	if (state == 1) {
		multipleRenderTargets->showTextures(width, height);
	} else if (state == 0) {
		multipleRenderTargets->render(player->camera(), width, height);
	}

}

void DefRenderTestScene::bindTriangleData(){
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

void DefRenderTestScene::bindGeometry(int width, int height){
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
}