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
	state = 1;

	if (state == 0){
		vertexShader = new Shader("default_vertex.glsl", GL_VERTEX_SHADER);
		geometryShader = new Shader("default_geometry.glsl", GL_GEOMETRY_SHADER);
		fragmentShader = new Shader("default_fragment.glsl", GL_FRAGMENT_SHADER);
		shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });
	}
	else if (state == 1){
		vertexShader = new Shader("deferred_first_vertex.glsl", GL_VERTEX_SHADER);
		geometryShader = new Shader("deferred_first_geometry.glsl", GL_GEOMETRY_SHADER);
		fragmentShader = new Shader("deferred_first_fragment.glsl", GL_FRAGMENT_SHADER);
		shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });
	}

	secondVertexShader = new Shader("deferred_second_vertex.glsl", GL_VERTEX_SHADER);
	secondGeometryShader = new Shader("deferred_second_geometry.glsl", GL_GEOMETRY_SHADER);
	secondFragmentShader = new Shader("deferred_second_fragment.glsl", GL_FRAGMENT_SHADER);
	secondShaderProgram = new ShaderProgram({ secondVertexShader, secondGeometryShader, secondFragmentShader });


	shaderProgram->use();

	// Texture unit 0 is for base images.
	glUniform1i(shaderProgram->uniformLocation("baseImage"), 0);

	geometry = new Cube();
	bindTriangleData();

	player = new Player();
	player->setMovementSpeed(1000.0f);
	multiplerendertargets = new FrameBufferObjects(settings::displayWidth(), settings::displayHeight());

	//Stämmer shaders callsen?
	diffuseID = glGetUniformLocation(shaderProgram->uniformLocation("shaderProgram"), "tDiffuse");
	positionID = glGetUniformLocation(shaderProgram->uniformLocation("shaderProgram"), "tPosition");
	normalID = glGetUniformLocation(shaderProgram->uniformLocation("shaderProgram"), "tNormal");
}

DefRenderTestScene::~DefRenderTestScene() {
	delete texture;

	delete multiplerendertargets;
	delete firstShaderProgram;
	delete secondShaderProgram;
	delete shaderProgram;
	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	glDeleteBuffers(1, &gVertexBuffer);
	glDeleteBuffers(1, &gIndexBuffer);


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

	multiplerendertargets->begin();

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

	glUniformMatrix4fv(shaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("viewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix3fv(shaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(N)[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);

	// Light information.
	glm::vec4 lightPosition = view * glm::vec4(-5.f, 0.f, 5.f, 1.f);
	glm::vec3 lightIntensity(1.f, 1.f, 1.f);
	glm::vec3 diffuseKoefficient(1.f, 1.f, 1.f);

	glUniform4fv(shaderProgram->uniformLocation("lightPosition"), 1, &lightPosition[0]);
	glUniform3fv(shaderProgram->uniformLocation("lightIntensity"), 1, &lightIntensity[0]);
	glUniform3fv(shaderProgram->uniformLocation("diffuseKoefficient"), 1, &diffuseKoefficient[0]);

	// Draw the triangles
	//glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);

	multiplerendertargets->end();

	//deferredRender(width, height);
	multiplerendertargets->showTexture(0, 512, 384, 0);
	multiplerendertargets->showTexture(1, 512, 384, 512);
	multiplerendertargets->showTexture(2, 512, 384, 0, 384);
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

	GLuint vertexPos = shaderProgram->attributeLocation("vertex_position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(0));

	GLuint vertexNormal = shaderProgram->attributeLocation("vertex_normal");
	glVertexAttribPointer(vertexNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float)* 3));

	GLuint vertexTexture = shaderProgram->attributeLocation("vertex_texture");
	glVertexAttribPointer(vertexTexture, 2, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float)* 6));

	// Index buffer
	indexCount = geometry->indexCount();
	glGenBuffers(1, &gIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), geometry->indices(), GL_STATIC_DRAW);
	
}
void DefRenderTestScene::deferredRender(int width, int height){

	secondShaderProgram->use();

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, fboRT->getDiffuseTex());
	glUniform1i(diffuseID, 0);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, fboRT->getPositionTex());
	glUniform1i(positionID, 1);

	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, fboRT->getNormalTex());
	glUniform1i(normalID, 2);

	// Render the quad
	glLoadIdentity();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, -1.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f((float)width, 0.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f((float)width, (float)height, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, (float)height, 0.0f);
	glEnd();

	// Reset OpenGL state
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	//glUseProgramObject(0);



};