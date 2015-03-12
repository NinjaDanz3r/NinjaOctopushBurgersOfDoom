#ifndef __FRUSTUMSCENE_H__
#define __FRUSTUMSCENE_H__

#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "GeometryObject.h"
#include "Player.h"
#include "FrameBufferObjects.h"
#include <vector>

/** @ingroup game
* @{
*/

/// %Scene used to test picking.
class FrustumScene : public Scene {
public:
	/// Constructor
	FrustumScene();

	/// Destructor
	/**
	* Free allocated resources.
	*/
	~FrustumScene();

	/// Update the scene.
	/**
	* @param time Time since last frame (in seconds).
	* @return SceneEnd-struct defining what to do next. nullptr if nothing should be done
	*/
	SceneEnd* update(double time);

	/// Render the scene.
	/**
	* @param width Width of the context.
	* @param height Height of the context.
	*/
	void render(int width, int height);

private:
	FrameBufferObjects* multipleRenderTargets;
	int state; // 0 == deferred render, 1== display textures.
	// Shaders
	Shader* vertexShader;
	Shader* geometryShader;
	Shader* fragmentShader;
	ShaderProgram* shaderProgram;
	// Shaders lighting pass
	Shader* deferredVertexShader;
	Shader* deferredFragmentShader;
	ShaderProgram* deferredShaderProgram;

	Texture* diffuse;
	Texture* normal;
	Texture* specular;

	Texture* texture;
	Geometry* geometry;
	std::vector<GeometryObject*> multiGeometry;
	int numModels = 850;
	Player* player;
};

/** @} */

#endif