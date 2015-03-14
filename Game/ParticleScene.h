#ifndef __PARTICLESCENE_H__
#define __PARTICLESCENE_H__

#include "Scene.h"

class Shader;
class ShaderProgram;
class Texture;
class Player;
class ParticleSystem;

/** @ingroup game
 * @{
 */

/// %Scene used to test the ParticleSystem.
class ParticleScene : public Scene {
	public:
		/// Constructor
		ParticleScene();

		/// Destructor
		/**
		* Free allocated resources.
		*/
		~ParticleScene();

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
		//Shaders
		Shader* fragmentShader;
		Shader* geometryShader;
		Shader* vertexShader;
		ShaderProgram* shaderProgram;
		Texture* texture;

		Player* player;
		ParticleSystem* particleSystem;
};

/** @} */

#endif