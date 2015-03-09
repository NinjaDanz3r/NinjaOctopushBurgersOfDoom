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
	fragmentShader = new Shader("picking_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	shaderProgram->use();

	// Texture unit 0 is for base images.
	glUniform1i(shaderProgram->uniformLocation("baseImage"), 0);
	// Texture unit 1 is for normal map.
	glUniform1i(shaderProgram->uniformLocation("normalMap"), 1);
	// Texture unit 0 is for specular map.
	glUniform1i(shaderProgram->uniformLocation("specularMap"), 2);

	for (int i = 0; i < numModels; i++){
		Geometry* tempGeometry = new Model("Resources/Models/rock01/rock_01.obj");
		tempGeometry->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
		int rand1 = rand() % 11 - 5;
		int rand2 = rand() % 11 - 5;
		int rand3 = -10 - rand() % 10;
		tempGeometry->setPosition(glm::vec3( (float)rand1, (float)rand2, (float)rand3) );
		rand1 = rand() % 361;
		rand2 = rand() % 361;
		rand3 = rand() % 361;
		tempGeometry->setRotation((float)rand1, (float)rand2, (float)rand3);
		multiGeometry.push_back(tempGeometry);
	}
	//geometry = new Model("Resources/Models/rock01/rock_01.obj");
	//geometry->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
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
	for (int i = 0; i < numModels; i++)
	{
		glDeleteBuffers(1, &vertexBuffers[i]);
		glDeleteBuffers(1, &indexBuffers[i]);
	}


	//delete geometry;
	delete player;
}

Scene::SceneEnd* PickingScene::update(double time) {
	player->update(time);

	return nullptr;
}

void PickingScene::render(int width, int height) {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float closestDistance = std::numeric_limits<float>::max();

	// Send the matrices to the shader (Per render call operations).
	glm::mat4 view = player->camera()->view();
	glm::mat4 proj = player->camera()->projection(width, height);
	//create mouse ray
	float x, y;
	x = static_cast<float>(input::cursorX());
	y = static_cast<float>(input::cursorY());
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

	// Base image texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse->textureID());

	// Normal map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normal->textureID());

	// Specular map
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, specular->textureID());

	glUniformMatrix4fv(shaderProgram->uniformLocation("viewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(shaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);

	// Light information.
	glm::vec4 lightPosition = view * glm::vec4(-5.f, 0.f, 5.f, 1.f);
	glm::vec3 lightIntensity(1.f, 1.f, 1.f);
	glm::vec3 diffuseKoefficient(1.f, 1.f, 1.f);
	glUniform4fv(shaderProgram->uniformLocation("lightPosition"), 1, &lightPosition[0]);
	glUniform3fv(shaderProgram->uniformLocation("lightIntensity"), 1, &lightIntensity[0]);
	glUniform3fv(shaderProgram->uniformLocation("diffuseKoefficient"), 1, &diffuseKoefficient[0]);

	for (int i = 0; i < numModels; i++)
	{
		glBindVertexArray(vertexAttributes[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[i]);

		Geometry* currGeometry = multiGeometry[i];
		// Model matrix, unique for each model.
		glm::mat4 model = currGeometry->modelMatrix();

		glm::mat4 MV = view * model;
		glm::mat4 N = glm::transpose(glm::inverse(MV));

		//Ray in world space
		glm::vec4 rayOrigin(0.0f, 0.0f, 0.0f, 1.0f);
		rayOrigin = inverseView*(rayOrigin);
		glm::vec4 rayWor = glm::vec4(inverseView*rayEye);
		//ray in local space
		glm::mat4 inverseModel = glm::inverse(model);
		rayOrigin = inverseModel*(rayOrigin);
		glm::vec3 rayMod = glm::vec3(inverseModel*rayWor);
		rayWor = glm::normalize(rayWor);

		//Search for hits.
		float distance;
		bool hit = false;
		int passes = 0;

		for (int i = 0; (i < currGeometry->indexCount()) && (hit == false); i += 3) {
			passes++;
			int ind1, ind2, ind3;
			ind1 = currGeometry->indices()[i];
			ind2 = currGeometry->indices()[i + 1];
			ind3 = currGeometry->indices()[i + 2];

			Geometry::Vertex vert1 = currGeometry->vertices()[ind1];
			Geometry::Vertex vert2 = currGeometry->vertices()[ind2];
			Geometry::Vertex vert3 = currGeometry->vertices()[ind3];

			hit = rayVsTri(vert1.position, vert2.position, vert3.position, glm::vec3(rayMod), glm::vec3(rayOrigin), distance);
		}
		// Hitdata
		glUniform1i(shaderProgram->uniformLocation("isHit"), hit);
		//fprintf(stderr, "Hit: %i Distance: %f Passes:%i\n", hit, distance, passes);
		//fprintf(stderr, "Raydir: %f %f %f\n", rayWor.x, rayWor.y, rayWor.z);
		//fprintf(stderr, "RayO: %f %f %f\n", rayOrigin.x, rayOrigin.y, rayOrigin.z);
		//fflush(stderr);
		
		glUniformMatrix4fv(shaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix3fv(shaderProgram->uniformLocation("normalMatrix"), 1, GL_FALSE, &glm::mat3(N)[0][0]);

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
	}
}

void PickingScene::bindTriangleData() {
	// Vertex buffer
	vertexBuffers = new GLuint[numModels];
	vertexAttributes = new GLuint[numModels];
	indexBuffers = new GLuint[numModels];
	for (int i = 0; i < numModels; i++)
	{
		vertexCount = multiGeometry[i]->vertexCount();
		glGenBuffers(1, &vertexBuffers[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[i]);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Geometry::Vertex), multiGeometry[0]->vertices(), GL_STATIC_DRAW);

		// Define vertex data layout
		glGenVertexArrays(1, &vertexAttributes[i]);
		glBindVertexArray(vertexAttributes[i]);
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
		indexCount = multiGeometry[i]->indexCount();
		glGenBuffers(1, &indexBuffers[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), multiGeometry[i]->indices(), GL_STATIC_DRAW);
	}
}