#ifndef __MORPHSCENE_H__
#define __MORPHSCENE_H__

#include "Scene.h"
#include <glm/glm.hpp>

class FrameBufferObjects;
class Shader;
class ShaderProgram;
class Texture;
class Geometry;
class GeometryObject;
class Player;

/** @ingroup game
* @{
*/

/// %Scene used to test morph animation.
class MorphScene : public Scene {
public:
	/// Constructor
	MorphScene();

	/// Destructor
	/**
	* Free allocated resources.
	*/
	~MorphScene();

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
	Geometry* geometry;
	glm::vec3* targetPositions;
	float t = 0.f;
	bool direction;
	GeometryObject* geometryObject;
	Player* player;
};

/** @} */

#endif