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

	player = new Player();
	player->setMovementSpeed(100.0f);
	multiplerendertargets = new FrameBufferObjects();
	shadowMap = new ShadowMapping();

	geometryGround = new Cube();
	geometryGround->setScale(5.0, 5.0, 5.0);
	geometryGround->setPosition(0.5, -3.0, -2.0);

	geometry = new Cube();
	bindTriangleData();
	verticesShadowBox = new ShadowBox[vertexCount];
	verticesShadowBox[0].position = glm::vec3(0.5f, 0.5f, 0.5f);
	verticesShadowBox[1].position = glm::vec3(-0.5f, -0.5f, 0.5f);
	verticesShadowBox[2].position = glm::vec3(0.5f, -0.5f, 0.5f);
	verticesShadowBox[3].position = glm::vec3(-0.5f, 0.5f, 0.5f);

	// Side 2
	verticesShadowBox[4].position = glm::vec3(-0.5f, 0.5f, -0.5f);
	verticesShadowBox[5].position = glm::vec3(-0.5f, -0.5f, -0.5f);
	verticesShadowBox[6].position = glm::vec3(-0.5f, -0.5f, 0.5f);
	verticesShadowBox[7].position = glm::vec3(-0.5f, 0.5f, 0.5f);

	// Side 3
	verticesShadowBox[8].position = glm::vec3(0.5f, 0.5f, -0.5f);
	verticesShadowBox[9].position = glm::vec3(0.5f, -0.5f, -0.5f);
	verticesShadowBox[10].position = glm::vec3(0.5f, -0.5f, 0.5f);
	verticesShadowBox[11].position = glm::vec3(0.5f, 0.5f, 0.5f);

	// Side 4
	verticesShadowBox[12].position = glm::vec3(0.5f, 0.5f, -0.5f);
	verticesShadowBox[13].position = glm::vec3(-0.5f, -0.5f, -0.5f);
	verticesShadowBox[14].position = glm::vec3(0.5f, -0.5f, -0.5f);
	verticesShadowBox[15].position = glm::vec3(-0.5f, 0.5f, -0.5f);

	// Side 5
	verticesShadowBox[16].position = glm::vec3(-0.5f, -0.5f, 0.5f);
	verticesShadowBox[17].position = glm::vec3(0.5f, -0.5f, 0.5f);
	verticesShadowBox[18].position = glm::vec3(0.5f, -0.5f, -0.5f);
	verticesShadowBox[19].position = glm::vec3(-0.5f, -0.5f, -0.5f);

	// Side 6
	verticesShadowBox[20].position = glm::vec3(-0.5f, 0.5f, 0.5f);
	verticesShadowBox[21].position = glm::vec3(0.5f, 0.5f, 0.5f);
	verticesShadowBox[22].position = glm::vec3(0.5f, 0.5f, -0.5f);
	verticesShadowBox[23].position = glm::vec3(-0.5f, 0.5f, -0.5f);
	bindShadowGeometry();
	bindDeferredQuad();
	bindGroundGeometry();

	//shaderProgram->use();
	//Only need tDiffuse for holding the texture during geometry call.
	//diffuseID = shaderProgram->uniformLocation("tDiffuse");
	//glUniform1i(diffuseID, 0);

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

	glDeleteBuffers(1, &shadowVertexBuffer);
	glDeleteBuffers(1, &shadowIndexBuffer);

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
	shadowShaderProgram->use();
	//multiplerendertargets->bindForWriting();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_BLEND);

	glViewport(0, 0, width, height);
	
	//bindGeometry(width,height,geometry);
	// Model matrix, unique for each model.
	glm::mat4 model = geometry->modelMatrix();

	glUniformMatrix4fv(shaderProgram->uniformLocation("modelMatrix"), 1, GL_FALSE, &model[0][0]);




	//shadowMap->bindForWriting();
	//glDrawBuffer(GL_NONE);
	shadowRender(width, height);

	/*shaderProgram->use();	
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
	}*/
	
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
	//glEnable(GL_BLEND);
	//glBlendEquation(GL_FUNC_ADD);
	//glBlendFunc(GL_ONE, GL_ONE);

	shadowMap->bindForReading(GL_TEXTURE3);
	bindLighting(width, height);
	multiplerendertargets->bindForReading();


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

	shadowShaderProgram->use();
	shadowMap->bindForReading(GL_TEXTURE3);
	glReadBuffer(GL_DEPTH_ATTACHMENT);
	glBlitFramebuffer(0, 0, width, height, halfWidth, 0, width, halfHeight, GL_DEPTH_BUFFER_BIT, GL_LINEAR);

}
void DefRenderTestScene::bindGeometry(int width, int height,Geometry* geometry){
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

	glm::vec4 lightPosition = view * glm::vec4(0.f, 3.f, 3.f, 1.f);
	glm::vec3 lightIntensity(1.f, 1.f, 1.f);
	glm::vec3 diffuseKoefficient(1.f, 1.f, 1.f);
	glm::vec2 screenSize(width, height);

	// Model matrix, unique for each model.
	glm::mat4 model = geometry->modelMatrix();
	glm::vec3 position = glm::vec3(0.f, 0.f, 3.f);
	glm::mat4 UVMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);

	glm::mat4 viewInverse = glm::inverse(view);

	// Send the matrices to the shader.
	glm::mat4 viewMatrix = glm::lookAt(position, geometry->position() , glm::vec3(0, 1, 0));
	glm::mat4 perspectiveMatrix = glm::perspective(180.0f, static_cast<float>(width) / height, 0.5f, 1000.0f);

	shadowID = secondShaderProgram->uniformLocation("tShadowMap");
	diffuseID = secondShaderProgram->uniformLocation("tDiffuse");
	positionID = secondShaderProgram->uniformLocation("tPosition");
	normalID = secondShaderProgram->uniformLocation("tNormals");

	glUniform1i(positionID, FrameBufferObjects::POSITION);
	glUniform1i(diffuseID, FrameBufferObjects::DIFFUSE);
	glUniform1i(normalID, FrameBufferObjects::NORMAL);
	glUniform1i(shadowID, 3);


	glUniformMatrix4fv(secondShaderProgram->uniformLocation("UVtransformMatrix"), 1, GL_FALSE, &UVMatrix[0][0]);
	glUniformMatrix4fv(secondShaderProgram->uniformLocation("inverseViewMatrix"), 1, GL_FALSE, &viewInverse[0][0]);
	glUniformMatrix4fv(secondShaderProgram->uniformLocation("lightViewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(secondShaderProgram->uniformLocation("lightProjectionMatrix"), 1, GL_FALSE, &perspectiveMatrix[0][0]);

	glUniform2fv(secondShaderProgram->uniformLocation("screenSize"), 1, &screenSize[0]);
	glUniform4fv(secondShaderProgram->uniformLocation("lightPosition"), 1, &lightPosition[0]);
	glUniform3fv(secondShaderProgram->uniformLocation("lightIntensity"), 1, &lightIntensity[0]);
	glUniform3fv(secondShaderProgram->uniformLocation("diffuseKoefficient"), 1, &diffuseKoefficient[0]);
}
void DefRenderTestScene::shadowRender(int width, int height){
	glBindVertexArray(shadowVertexAttribute);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shadowIndexBuffer);

	glClear(GL_DEPTH_BUFFER_BIT);

	// Model matrix, unique for each model.
	glm::mat4 model = geometry->modelMatrix();
	glm::vec3 position = glm::vec3(0.f, 3.f, 3.f);

	// Send the matrices to the shader.
	glm::mat4 viewMatrix = glm::lookAt(position, geometry->position(), glm::vec3(0, 1, 0));
	glm::mat4 perspectiveMatrix = glm::perspective(45.0f, 1.0f, 2.0f, 50.0f);

	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightmodelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightViewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(shadowShaderProgram->uniformLocation("lightProjectionMatrix"), 1, GL_FALSE, &perspectiveMatrix[0][0]);

	//Render main geometry 
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void DefRenderTestScene::bindShadowGeometry(){

	// Vertex buffer
	glGenBuffers(1, &shadowVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, shadowVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(DefRenderTestScene::ShadowBox), verticesShadowBox, GL_STATIC_DRAW);

	// Define vertex data layout
	glGenVertexArrays(1, &shadowVertexAttribute);
	glBindVertexArray(shadowVertexAttribute);
	glEnableVertexAttribArray(0); //the vertex attribute object will remember its enabled attributes

	GLuint shadowVertexPos = shadowShaderProgram->attributeLocation("vertex_position");
	glVertexAttribPointer(shadowVertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(DefRenderTestScene::ShadowBox), BUFFER_OFFSET(0));

	// Index buffer
	glGenBuffers(1, &shadowIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shadowIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), geometry->indices(), GL_STATIC_DRAW);
}
void DefRenderTestScene::bindGroundGeometry(){
	vertexCount = geometryGround->vertexCount();
	glGenBuffers(1, &groundVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, groundVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Geometry::Vertex), geometryGround->vertices(), GL_STATIC_DRAW);

	// Define vertex data layout
	glGenVertexArrays(1, &groundVertexAttribute);
	glBindVertexArray(groundVertexAttribute);
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