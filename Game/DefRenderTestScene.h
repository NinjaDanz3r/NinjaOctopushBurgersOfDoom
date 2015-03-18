#ifndef __DEFRENDERTESTSCENE_H__
#define __DEFRENDERTESTSCENE_H__

#include "FrameBufferObjects.h"
#include "Scene.h"

class FrameBufferObjects;
class ShadowMapping;
class Geometry;
class GeometryObject;
class Shader;
class ShaderProgram;
class Texture;
class Player;

/** @ingroup game
* @{
*/

/// Test deferred rendering and shadow mapping.
class DefRenderTestScene : public Scene {
	public:
		/// Constructor
		DefRenderTestScene();

		/// Destructor
		/**
		* Free allocated resources.
		*/
		~DefRenderTestScene();

		/// Update the scene.
		/**
		* @param time Time since last frame (in seconds).
		* @return SceneEnd-struct defining what to do next. nullptr if nothing should be done
		*/
		SceneEnd* update(double time);

		/// Render the geometry in the scene.
		/**
		* @param width Width of the context.
		* @param height Height of the context.
		*/
		void render(int width, int height);

	private:
		void renderShadows(int width, int height);

		FrameBufferObjects* multipleRenderTargets;
		ShadowMapping* shadowMap;

		Geometry* geometry;
		GeometryObject* geometryObject;
		GeometryObject* geometryGround;

		// Shaders geometry pass
		Shader* vertexShader;
		Shader* geometryShader;
		Shader* fragmentShader;
		ShaderProgram* shaderProgram;

		// Shaders lighting pass
		Shader* deferredVertexShader;
		Shader* deferredFragmentShader;
		ShaderProgram* deferredShaderProgram;

		// Shaders shadows pass
		Shader* shadowVertexShader;
		Shader* shadowFragmentShader;
		ShaderProgram* shadowShaderProgram;

		// Misc
		Texture* texture;
		Player* player;
};
#endif
