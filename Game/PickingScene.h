#ifndef __PICKINGSCENE_H__
#define __PICKINGSCENE_H__

#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "GeometryObject.h"
#include "Player.h"
#include <vector>

/** @ingroup game
* @{
*/

/// %Scene used to test picking.
class PickingScene : public Scene {
	public:
		/// Constructor
		PickingScene();

		/// Destructor
		/**
		* Free allocated resources.
		*/
		~PickingScene();

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
		// Shaders
		Shader* vertexShader;
		Shader* geometryShader;
		Shader* fragmentShader;
		ShaderProgram* shaderProgram;
		Texture* diffuse;
		Texture* normal;
		Texture* specular;
		AABB aabb;

		Texture* texture;
		Geometry* geometry;
		std::vector<GeometryObject*> multiGeometry;
		int numModels = 850;
		Player* player;

		GLuint hitData = 1;
		GLuint hitAttrib = 1;

		GLboolean isHit = false;
};

/** @} */

#endif