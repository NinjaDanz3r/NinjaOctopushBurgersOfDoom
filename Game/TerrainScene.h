#ifndef __TERRAINSCENE_H__
#define __TERRAINSCENE_H__

#include "Scene.h"

class FrameBufferObjects;
class Shader;
class ShaderProgram;
class Texture;
class Terrain;
class TerrainObject;
class Player;
class Skybox;
class CubeMapTexture;

/** @ingroup game
 * @{
 */

/// %Scene used to test terrain (height maps).
class TerrainScene : public Scene {
	public:
		/// Constructor
		TerrainScene();

		/// Destructor
		/**
		* Free allocated resources.
		*/
		~TerrainScene();

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

		Texture* blendMap;
		Texture* grassTexture;
		Texture* cliffTexture;
		Texture* sandTexture;
		Texture* snowTexture;
		Terrain* terrain;
		TerrainObject* terrainObject;
		Player* player;

		// Skybox
		Skybox* skybox;
		CubeMapTexture* skyboxTexture;
};

/** @} */

#endif