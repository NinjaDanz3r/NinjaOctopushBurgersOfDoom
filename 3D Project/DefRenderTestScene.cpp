#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW\glfw3.h>
#include "DefRenderTestScene.h"
#include "Square.h"
#include "Texture2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

DefRenderTestScene::DefRenderTestScene() {
	texture = new Texture2D("Resources/Textures/bth_image.tga");

	vertexShader = new Shader("default_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("default_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("default_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	firstVertexShader = new Shader("deferred_first_vertex.glsl", GL_VERTEX_SHADER);
	firstGeometryShader = new Shader("deferred_first_geometry.glsl", GL_GEOMETRY_SHADER);
	firstFragmentShader = new Shader("deferred_first_fragment.glsl", GL_FRAGMENT_SHADER);
	firstShaderProgram = new ShaderProgram({ firstVertexShader, firstGeometryShader, firstFragmentShader });

	secondVertexShader = new Shader("deferred_second_vertex.glsl", GL_VERTEX_SHADER);
	secondGeometryShader = new Shader("deferred_second_geometry.glsl", GL_GEOMETRY_SHADER);
	secondFragmentShader = new Shader("deferred_second_fragment.glsl", GL_FRAGMENT_SHADER);
	secondShaderProgram = new ShaderProgram({ secondVertexShader, secondGeometryShader, secondFragmentShader });

	state = 0;
	if (state == 0)
		currentShaderProgram = shaderProgram;
	else
		currentShaderProgram = firstShaderProgram;

	currentShaderProgram->use();

	// Texture unit 0 is for base images.
	glUniform1i(currentShaderProgram->uniformLocation("baseImage"), 0);

	geometry = new Cube();
	bindTriangleData();

	player = new Player();
	player->setMovementSpeed(10.0f);
	multiplerendertargets = new FrameBufferObjects(settings::displayWidth(), settings::displayHeight());

	//Stämmer shaders callsen?
	diffuseID = glGetUniformLocationARB(currentShaderProgram->uniformLocation("shaderProgram"), "tDiffuse");
	positionID = glGetUniformLocationARB(currentShaderProgram->uniformLocation("shaderProgram"), "tPosition");
	normalID = glGetUniformLocationARB(currentShaderProgram->uniformLocation("shaderProgram"), "tNormal");
}

DefRenderTestScene::~DefRenderTestScene() {
	delete texture;

	delete currentShaderProgram;
	delete firstShaderProgram;
	delete secondShaderProgram;
	delete shaderProgram;
	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	delete geometry;
	delete player;
}

Scene::SceneEnd* DefRenderTestScene::update(double time) {
	player->update(time);
	geometry->rotate(1, 2, 1);
	return nullptr;
}

void DefRenderTestScene::render(int width, int height) {
	//Nästa steg fixa render funktion för att reflektera DefferedRender + model render
	//Sen shaders.
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);

	//multiplerendertargets->begin();
	
	glBindVertexArray(gVertexAttribute);

	// Base image texture
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());

	// Model matrix, unique for each model.
	glm::mat4 model = geometry->modelMatrix();

	// Send the matrices to the shader.
	glm::mat4 view = player->camera()->view();
	glm::mat4 MV = view * model;
	glm::mat4 N = glm::transpose(glm::inverse(MV));

	glUniformMatrix4fv(currentShaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(currentShaderProgram->uniformLocation("viewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix3fv(currentShaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(N)[0][0]);
	glUniformMatrix4fv(currentShaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);

	// Light information.
	glm::vec4 lightPosition = view * glm::vec4(-5.f, 0.f, 5.f, 1.f);
	glm::vec3 lightIntensity(1.f, 1.f, 1.f);
	glm::vec3 diffuseKoefficient(1.f, 1.f, 1.f);

	glUniform4fv(currentShaderProgram->uniformLocation("lightPosition"), 1, &lightPosition[0]);
	glUniform3fv(currentShaderProgram->uniformLocation("lightIntensity"), 1, &lightIntensity[0]);
	glUniform3fv(currentShaderProgram->uniformLocation("diffuseKoefficient"), 1, &diffuseKoefficient[0]);

	// Draw the triangles
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);

	//multiplerendertargets->end();

}

void DefRenderTestScene::bindTriangleData() {
	// Vertex buffer
	vertexCount = geometry->vertexCount();
	glGenBuffers(1, &gVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Geometry::Vertex), geometry->vertices(), GL_STATIC_DRAW);

	// Define vertex data layout
	glGenVertexArrays(1, &gVertexAttribute);
	glBindVertexArray(gVertexAttribute);
	glEnableVertexAttribArray(0); //the vertex attribute object will remember its enabled attributes
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	GLuint vertexPos = currentShaderProgram->attributeLocation("vertex_position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(0));

	GLuint vertexNormal = currentShaderProgram->attributeLocation("vertex_normal");
	glVertexAttribPointer(vertexNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float)* 3));

	GLuint vertexTexture = currentShaderProgram->attributeLocation("vertex_texture");
	glVertexAttribPointer(vertexTexture, 2, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float)* 6));

	// Index buffer
	indexCount = geometry->indexCount();
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), geometry->indices(), GL_STATIC_DRAW);
	
	
	/*vertexCount = testCube->count();

	// Create buffer and set data
	glGenBuffers(1, &gVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::TriangleVertex) * testCube->count(), testCube->vertexes(), GL_STATIC_DRAW);

	// Define vertex data layout
	glGenVertexArrays(1, &gVertexAttribute);
	glBindVertexArray(gVertexAttribute);
	glEnableVertexAttribArray(0); //the vertex attribute object will remember its enabled attributes
	glEnableVertexAttribArray(1);

	GLuint vertexPos = glGetAttribLocation(shaders->shaderProgram(), "vertex_position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(Cube::TriangleVertex), BUFFER_OFFSET(0));

	GLuint vertexTexture = glGetAttribLocation(shaders->shaderProgram(), "vertex_texture");
	glVertexAttribPointer(vertexTexture, 2, GL_FLOAT, GL_FALSE, sizeof(Cube::TriangleVertex), BUFFER_OFFSET(sizeof(float)* 3));*/
}