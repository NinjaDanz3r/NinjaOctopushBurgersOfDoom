#ifndef __DEFRENDERTESTSCENE_H__
#define __DEFRENDERTESTSCENE_H__

#include "FrameBufferObjects.h"
#include "Scene.h"
#include "settings.h"
#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Geometry.h"
#include "Player.h"
#include "Cube.h"

class DefRenderTestScene :public Scene
{
public:
	// Constructor
	DefRenderTestScene();

	// Destructor
	~DefRenderTestScene();

	// Updates the scene.
	SceneEnd* update(double time);
	void bindGeometry(int width, int height);
	void bindLighting(int width, int height);


	// Renders the scene.
	void render(int width, int height);
	void deferredRender(int width, int height);
	void showTex(int width, int height);
private:
	void bindTriangleData();	
	void bindDeferredQuad();

	GLuint diffuseID;
	GLuint positionID;
	GLuint normalID;

	FrameBufferObjects* multiplerendertargets;

	//Shaders
	Geometry* geometry;
	Geometry* lightSquare;
	Shader* vertexShader;
	Shader* geometryShader;
	Shader* fragmentShader;
	ShaderProgram* shaderProgram;

	Shader* firstVertexShader;
	Shader* firstGeometryShader;
	Shader* firstFragmentShader;
	ShaderProgram* firstShaderProgram;

	Shader* secondVertexShader;
	Shader* secondGeometryShader;
	Shader* secondFragmentShader;
	ShaderProgram* secondShaderProgram;

	//Misc
	int state; //0 == normal render, 1== deferred rendering.
	Texture* texture;
	Cube* testCube;
	Player* player;
	GLuint halfWidth;
	GLuint halfHeight;

	// Vertex buffer
	GLuint gVertexBuffer = 0;
	GLuint gVertexAttribute = 0;

	//Index buffer
	GLuint gIndexBuffer = 0;
	unsigned int indexCount = 0;
	int vertexCount = 0;

	
};
#endif
