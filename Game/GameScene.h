#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "Scene.h"

class FrameBufferObjects;
class Shader;
class ShaderProgram;
class Texture;
class Geometry;
class GeometryObject;
class Player;
class ParticleSystem;

/** @ingroup game
* @{
*/

/// Intense game!
class GameScene : public Scene {
public:
	/// Constructor
	GameScene();

	/// Destructor
	/**
	* Free allocated resources.
	*/
	~GameScene();

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

	// Shaders
	Shader* vertexShader;
	Shader* geometryShader;
	Shader* fragmentShader;
	ShaderProgram* shaderProgram;

	// Particle shaders
	Shader* particleVertexShader;
	Shader* particleGeometryShader;
	Shader* particleFragmentShader;
	ShaderProgram* particleShaderProgram;

	// Shaders lighting pass
	Shader* deferredVertexShader;
	Shader* deferredFragmentShader;
	ShaderProgram* deferredShaderProgram;

	Texture* diffuse;
	Texture* normal;
	Texture* specular;
	Geometry* geometry;
	GeometryObject* geometryObject;
	Player* player;

	Texture* particleTexture;
	ParticleSystem* particleSystem;
};

/** @} */

#endif