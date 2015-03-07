#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW\glfw3.h>

#include "PickingScene.h"
#include "IntersectionTesting.h"

#include "Square.h"
#include "Texture2D.h"
#include "input.h"
#include "Model.h"

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
	fragmentShader = new Shader("normalspecularmap_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	shaderProgram->use();

	// Texture unit 0 is for base images.
	glUniform1i(shaderProgram->uniformLocation("baseImage"), 0);
	// Texture unit 1 is for normal map.
	glUniform1i(shaderProgram->uniformLocation("normalMap"), 1);
	// Texture unit 0 is for specular map.
	glUniform1i(shaderProgram->uniformLocation("specularMap"), 2);

	geometry = new Model("Resources/Models/rock01/rock_01.obj");
	geometry->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
	bindTriangleData();

	player = new Player();
	player->setMovementSpeed(2.0f);
}

PickingScene::~PickingScene() {
	delete diffuse;
	delete normal;
	delete specular;

	delete shaderProgram;
	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);

	delete geometry;
	delete player;
}

Scene::SceneEnd* PickingScene::update(double time) {
	player->update(time);

	return nullptr;
}

void PickingScene::render(int width, int height) {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

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
	glm::mat4 model = geometry->modelMatrix();

	// Send the matrices to the shader.
	glm::mat4 view = player->camera()->view();
	glm::mat4 MV = view * model;
	glm::mat4 N = glm::transpose(glm::inverse(MV));

	//create mouse ray
	float x, y;
	x = static_cast<float>(input::cursorX());
	y = static_cast<float>(input::cursorY());
	glm::mat4 proj = player->camera()->projection(width, height);
	//Get NDC x and y
	float vx = ((2.0f * x) / width) - 1.0f;
	float vy = 1.0f - ((2.0f * y) / height);
	glm::vec4 rayOrigin(0.0f, 0.0f, 0.0f, 1.0f);
	
	//transform ray into local space
	glm::mat4 inverseModel = glm::inverse(model);
	glm::mat4 inverseView = glm::inverse(view);
	glm::mat4 inverseProj = glm::inverse(proj);
	
	//Ray in clip space
	glm::vec4 rayClip(vx, vy, -1.0f, 0.0f);
	
	//Ray in view space
	glm::vec4 rayEye = inverseProj*rayClip;
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);
	//Ray in world space
	rayOrigin = inverseView*(rayOrigin);
	glm::vec4 rayWor = glm::vec4(inverseView*rayEye);
	//ray in local space
	rayOrigin = inverseModel*(rayOrigin);
	glm::vec3 rayMod = glm::vec3(inverseModel*rayWor);
	rayWor = glm::normalize(rayWor);

	//Search for hits.
	float distance;
	bool hit = false;
	int passes = 0;
	
	for (int i = 0; (i < geometry->indexCount()) && (hit == false); i += 3) {
		passes++;
		int ind1, ind2, ind3;
		ind1 = geometry->indices()[i];
		ind2 = geometry->indices()[i+1];
		ind3 = geometry->indices()[i+2];

		Geometry::Vertex vert1 = geometry->vertices()[ind1];
		Geometry::Vertex vert2 = geometry->vertices()[ind2];
		Geometry::Vertex vert3 = geometry->vertices()[ind3];

		hit = rayVsTri(vert1.position, vert2.position, vert3.position, glm::vec3(rayMod), glm::vec3(rayOrigin), distance);
	}
	fprintf(stderr, "Hit: %i Distance: %f Passes:%i\n", hit, distance, passes);
	//fprintf(stderr, "Raydir: %f %f %f\n", rayWor.x, rayWor.y, rayWor.z);
	//fprintf(stderr, "RayO: %f %f %f\n", rayOrigin.x, rayOrigin.y, rayOrigin.z);
	fflush(stderr);
	
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
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
}

void PickingScene::bindTriangleData() {
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