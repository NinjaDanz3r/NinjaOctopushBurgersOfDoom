#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW\glfw3.h>
#include "DefRenderTestScene.h"
#include "Square.h"
#include "Texture2D.h"
#include "settings.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

DefRenderTestScene::RenderQuad DefRenderTestScene::vertices[4] = {{ -1.f, 1.f }, { 1.f, 1.f }, { -1.f, -1.f }, { 1.f, -1.f }};
unsigned int DefRenderTestScene::indices[6] = { 0, 1, 3, 0, 3, 2 };

struct CameraDirection
{
	GLenum cubemapFace;
	glm::vec3 target;
	glm::vec3 up;
};

CameraDirection cameraDirections[6] =
{
	{ GL_TEXTURE_CUBE_MAP_POSITIVE_X, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
	{ GL_TEXTURE_CUBE_MAP_NEGATIVE_X, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
	{ GL_TEXTURE_CUBE_MAP_POSITIVE_Y, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
	{ GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
	{ GL_TEXTURE_CUBE_MAP_POSITIVE_Z, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
	{ GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f) }
};


DefRenderTestScene::DefRenderTestScene() {
	texture = new Texture2D("Resources/Textures/kaleido.tga");
	state = 0;

	shadowVertexShader = new Shader("shadow_vertex.glsl", GL_VERTEX_SHADER);
	shadowFragmentShader = new Shader("shadow_fragment.glsl", GL_FRAGMENT_SHADER);
	shadowShaderProgram = new ShaderProgram({ shadowVertexShader, shadowFragmentShader });

	vertexShader = new Shader("deferred_first_vertex.glsl", GL_VERTEX_SHADER);
	geometryShader = new Shader("deferred_first_geometry.glsl", GL_GEOMETRY_SHADER);
	fragmentShader = new Shader("deferred_first_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, geometryShader, fragmentShader });

	secondVertexShader = new Shader("deferred_second_vertex.glsl", GL_VERTEX_SHADER);
	secondFragmentShader = new Shader("deferred_second_fragment.glsl", GL_FRAGMENT_SHADER);
	secondShaderProgram = new ShaderProgram({ secondVertexShader, secondFragmentShader });

	halfWidth = (GLint)(settings::displayWidth() / 2.0f);
	halfHeight = (GLint)(settings::displayHeight() / 2.0f);

	shaderProgram->use();

	player = new Player();
	player->setMovementSpeed(1000.0f);
	multiplerendertargets = new FrameBufferObjects();
	shadowMap = new ShadowMapping();

	geometry = new Cube();
	bindTriangleData();
	bindDeferredQuad();


	//Only need tDiffuse for holding the texture during geometry call.
	diffuseID = shaderProgram->uniformLocation("tDiffuse");
	glUniform1i(diffuseID, 0);

	shadowMap->begin(settings::displayWidth(), settings::displayHeight());
	multiplerendertargets->begin(settings::displayWidth(), settings::displayHeight());
}

DefRenderTestScene::~DefRenderTestScene() {
	delete texture;

	delete multiplerendertargets;
	delete secondShaderProgram;
	delete shaderProgram;

	delete secondVertexShader;
	delete secondFragmentShader;

	delete shadowShaderProgram;
	delete shadowVertexShader;
	delete shadowFragmentShader;

	delete vertexShader;
	delete geometryShader;
	delete fragmentShader;

	glDeleteBuffers(1, &gVertexBuffer);
	glDeleteBuffers(1, &gIndexBuffer);

	glDeleteBuffers(1, &qVertexBuffer);
	glDeleteBuffers(1, &qIndexBuffer);

	delete geometry;
	delete player;
}

Scene::SceneEnd* DefRenderTestScene::update(double time) {
	player->update(time);
	//geometry->rotate(1, 1, 1);
	return nullptr;
}

void DefRenderTestScene::render(int width, int height) {
	shaderProgram->use();
	multiplerendertargets->bindForWriting();

	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glViewport(0, 0, width, height);
	
	bindGeometry(width,height);

	shadowShaderProgram->use();

	glBindVertexArray(gVertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);

	for (unsigned int i = 0; i < 6; i++) {
		shadowMap->bindForWriting(cameraDirections[i].cubemapFace);
		shadowRender(width, height, i);
	}
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	//shaderProgram->use();
	multiplerendertargets->bindForWriting();
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID());
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);

	glDepthMask(GL_FALSE);
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

void DefRenderTestScene::bindTriangleData(){
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

	GLuint shadowVertexPos = shadowShaderProgram->attributeLocation("vertex_position");
	glVertexAttribPointer(shadowVertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(0));

	GLuint shadowVertexNormal = shadowShaderProgram->attributeLocation("vertex_normal");
	glVertexAttribPointer(shadowVertexNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float)* 3));

	GLuint shadowVertexTexture = shadowShaderProgram->attributeLocation("vertex_texture");
	glVertexAttribPointer(shadowVertexTexture, 2, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), BUFFER_OFFSET(sizeof(float)* 6));


	// Index buffer
	indexCount = geometry->indexCount();
	glGenBuffers(1, &gIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), geometry->indices(), GL_STATIC_DRAW);
	
}
void DefRenderTestScene::bindDeferredQuad(){
	qVertexCount = 4;
	glGenBuffers(1, &qVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, qVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, qVertexCount * sizeof(Geometry::Vertex), vertices, GL_STATIC_DRAW);

	// Define vertex data layout
	glGenVertexArrays(1, &qVertexAttribute);
	glBindVertexArray(qVertexAttribute);
	glEnableVertexAttribArray(0); //the vertex attribute object will remember its enabled attributes

	GLuint vertexPos = secondShaderProgram->attributeLocation("vertex_position");
	glVertexAttribPointer(vertexPos, 2, GL_FLOAT, GL_FALSE, sizeof(DefRenderTestScene::RenderQuad), BUFFER_OFFSET(0));

	// Index buffer
	qIndexCount = 6;
	glGenBuffers(1, &qIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, qIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, qIndexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

}
void DefRenderTestScene::deferredRender(int width, int height){
	secondShaderProgram->use();

	//Blending enabled for handling multiple light sources
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	bindLighting(width, height);
	multiplerendertargets->bindForReading();
	shadowMap->bindForReading(GL_TEXTURE3);

	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(qVertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, qIndexBuffer);


	glDrawElements(GL_TRIANGLES, qIndexCount, GL_UNSIGNED_INT, (void*)0);
}
void DefRenderTestScene::showTex(int width, int height){
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	multiplerendertargets->bindForTexReading();

	multiplerendertargets->setReadBuffer(FrameBufferObjects::POSITION);
	glBlitFramebuffer(0, 0, width, height, 0, 0, halfWidth, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	multiplerendertargets->setReadBuffer(FrameBufferObjects::DIFFUSE);
	glBlitFramebuffer(0, 0, width, height, 0, halfHeight, halfWidth, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	multiplerendertargets->setReadBuffer(FrameBufferObjects::NORMAL);
	glBlitFramebuffer(0, 0, width, height, halfWidth, halfHeight, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	//multiplerendertargets->setReadBuffer(FrameBufferObjects::DEPTH);
	//glBlitFramebuffer(0, 0, width, height, halfWidth, 0, width, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

}
void DefRenderTestScene::bindGeometry(int width, int height){
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
}
void DefRenderTestScene::bindLighting(int width, int height){
	//Bind light information for lighting pass
	glm::mat4 view = player->camera()->view();

	glm::vec4 lightPosition = view * glm::vec4(-5.f, 0.f, 5.f, 1.f);
	glm::vec3 lightIntensity(1.f, 1.f, 1.f);
	glm::vec3 diffuseKoefficient(1.f, 1.f, 1.f);
	glm::vec2 screenSize(width, height);

	shadowID = secondShaderProgram->uniformLocation("tShadowMap");
	diffuseID = secondShaderProgram->uniformLocation("tDiffuse");
	positionID = secondShaderProgram->uniformLocation("tPosition");
	normalID = secondShaderProgram->uniformLocation("tNormals");

	glUniform1i(positionID, FrameBufferObjects::POSITION);
	glUniform1i(diffuseID, FrameBufferObjects::DIFFUSE);
	glUniform1i(normalID, FrameBufferObjects::NORMAL);
	glUniform1i(shadowID, 3);

	glUniform2fv(secondShaderProgram->uniformLocation("screenSize"), 1, &screenSize[0]);
	glUniform4fv(secondShaderProgram->uniformLocation("lightPosition"), 1, &lightPosition[0]);
	glUniform3fv(secondShaderProgram->uniformLocation("lightIntensity"), 1, &lightIntensity[0]);
	glUniform3fv(secondShaderProgram->uniformLocation("diffuseKoefficient"), 1, &diffuseKoefficient[0]);
}
void DefRenderTestScene::shadowRender(int width, int height, int i){
	glBindVertexArray(gVertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Model matrix, unique for each model.
	glm::mat4 model = geometry->modelMatrix();
	glm::vec3 position = glm::vec3(-5.f, 0.f, 5.f);

	// Send the matrices to the shader.
	glm::mat4 viewMatrix = glm::lookAt(position, cameraDirections[i].target, cameraDirections[i].up);
	glm::vec4 lightPosition = viewMatrix * glm::vec4(-5.f, 0.f, 5.f, 1.f);

	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("projectionMatrix"), 1, GL_FALSE, &player->camera()->projection(width, height)[0][0]);
	glUniform4fv(shadowShaderProgram->uniformLocation("lightPosition"), 1, &lightPosition[0]);
 
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
}
