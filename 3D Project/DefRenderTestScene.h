#ifndef __DEFRENDERTESTSCENE_H__
#define __DEFRENDERTESTSCENE_H__

#include "FrameBufferObjects.h"
#include "Scene.h"
#include "settings.h"
#include "Shaders.h"
#include "Texture.h"
#include "Cube.h"
#include "Player.h"

class DefRenderTestScene :public Scene
{
public:
	// Constructor
	DefRenderTestScene();

	// Destructor
	~DefRenderTestScene();

	// Updates the scene.
	SceneEnd* update(double time);

	// Renders the scene.
	void render(int width, int height);

private:
	void bindTriangleData();

	GLuint diffuseID;
	GLuint positionID;
	GLuint normalID;

	FrameBufferObjects* multiplerendertargets;
	FrameBufferObjects* fboRT;

	Shaders* deffshaders;
	Shaders* shaders;
	Texture* texture;
	Cube* testCube;
	Player* player;

	// Vertex buffer.
	GLuint gVertexBuffer = 0;
	GLuint gVertexAttribute = 0;
	int vertexCount = 0;
};
#endif
