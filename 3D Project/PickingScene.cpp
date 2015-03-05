#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW\glfw3.h>

#include "PickingScene.h"

#include "Square.h"
#include "Texture2D.h"
#include "input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

#define EPSILON 0.00001

class AABB
{
public:
	glm::vec3 v1, v2, origin;
};

class OBB
{
public:
	glm::vec3 v1, v2, v3, origin, dim; //Dim: width, heigh, depth
};

//Möller-Trumbore intersection algorithm for triangles.
bool rayVsTri(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 rayDir, glm::vec3 rayOrigin, float* distance) {
	glm::vec3 edge1, edge2;
	glm::vec3 P, Q, T;
	float det, inverseDet, u, v, t;
	
	//Find triangle edge vectors
	edge1 = v2 - v1;
	edge2 = v3 - v1;
	P = glm::cross(rayDir, edge2);
	det = glm::dot(edge1, P);

	//If determinant is near zero, ray is in the triangle plane.
	if ((det > -EPSILON) && (det < EPSILON))
		return false;
	
	inverseDet = 1.0f / det;
	T = rayOrigin - v1;			//Distance from v1 to ray origin.
	u = dot(T, P) *inverseDet;

	//if u is outside 0..1 then the intersection is outside the triangle.
	if ((u < 0.0f) || (u > 1.0f)) 
		return false;

	Q = cross(T, edge1);
	v = dot(edge2, Q)*inverseDet;

	//If u+v exceeds 
	if ((v <0.0f) || (u + v > 1.0f))
		return false;

	//If all attempts to cull the ray has been passed, we have an intersection
	if (t > EPSILON){
		*distance = t;
		return true;
	}
	return false;
}

bool rayVsOBB(OBB obb, glm::vec3 rayDir, glm::vec3 rayOrigin, float *distance) {
	float tMin, tMax,t1,t2;
	tMin = std::numeric_limits<float>::lowest();
	tMax = std::numeric_limits<float>::max();
	
	glm::vec3 vArr[3];
	float dArr[3];
	vArr[0] = obb.v1; vArr[1] = obb.v2; vArr[2] = obb.v3;
	dArr[0] = obb.dim.x / 2; dArr[1] = obb.dim.y / 2; dArr[2] = obb.dim.z / 2;
	glm::vec3 P = obb.origin - rayOrigin;

	for (int i = 0; i < 3; i++){
		float e = glm::dot(vArr[i],P);
		float f = glm::dot(vArr[i], rayDir);
		if (fabs(f) > EPSILON)
		{
			t1 = (e + dArr[i]) / f;
			t2 = (e - dArr[i]) / f;
			if (t1 > t2)
				std::swap(t1, t2);
			if (t1 > tMin)
				tMin = t1;
			if (t2 < tMax)
				tMax = t2;
			if (tMin > tMax)
				return false;
			if (tMax < 0)
				return false;
		}
		else if ((-e - dArr[i] > 0) || (-e + dArr[i] < 0))
			return false;
	}
	if ((tMin > 0))
		*distance = tMin;
	else
		*distance = tMax;
	return;
}

PickingScene::PickingScene() {
	texture = new Texture2D("Resources/Textures/bth_image.tga");

	vertexShader = new Shader("default_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("default_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("default_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	shaderProgram->use();

	// Texture unit 0 is for base images.
	glUniform1i(shaderProgram->uniformLocation("baseImage"), 0);

	geometry = new Square();
	bindTriangleData();

	player = new Player();
	player->setMovementSpeed(2.0f);
}

PickingScene::~PickingScene() {
	delete texture;

	delete shaderProgram;
	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

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
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());

	// Model matrix, unique for each model.
	glm::mat4 model = geometry->modelMatrix();

	//Mouse ray.
	float x, y;
	x = static_cast<float>(input::cursorX());
	y = static_cast<float>(input::cursorY());
	glm::mat4 proj = player->camera()->projection(width, height);
	
	float vx = ((2.0f*x / width) - 1.0f) / (proj[0][0]);
	float vy = ((-2.0f*x / height) + 1.0f) / (proj[0][0]);

	glm::vec4 rayOrigin(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 rayDir(vx, vy, 1.0f, 0.0f);
	//transform into local space
	//local origin = orgin*inverse_world
	//local rayDir = rayDir*inverse_world


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