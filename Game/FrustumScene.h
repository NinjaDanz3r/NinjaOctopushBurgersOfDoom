#ifndef __FRUSTUMSCENE_H__
#define __FRUSTUMSCENE_H__

#include "Scene.h"
#include <vector>
#include <map>

class Shader;
class ShaderProgram;
class FrameBufferObjects;
class Texture;
class Geometry;
class GeometryObject;
class Player;
class QuadTree;

/** @ingroup game
* @{
*/

/// %Scene used to test frustum culling.
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

		Geometry* geometry;
		QuadTree* quadTree;

		std::map<GeometryObject*, GeometryObject*> geometryMap;

		std::vector<GeometryObject*> multiGeometry;
		const int numModels = 100;
		Player* player;
};

/** @} */

#endif