#ifndef __AUDIOSCENE_H__
#define __AUDIOSCENE_H__

#include "FrameBufferObjects.h"
#include "Scene.h"
#include <Shader.h>
#include <ShaderProgram.h>
#include <Texture.h>
#include <Geometry.h>
#include "GeometryObject.h"
#include "Player.h"
#include "WaveFile.h"
#include "SoundBuffer.h"
#include "Sound.h"

/** @ingroup game
 * @{
 */

/// %Scene used to test 3D audio.
class AudioScene : public Scene {
	public:
		/// Constructor
		AudioScene();

		/// Destructor
		/**
		 * Free allocated resources.
		 */
		~AudioScene();

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

		Texture* texture;
		Geometry* geometry;
		GeometryObject* geometryObject;
		Player* player;

		// Audio
		WaveFile* waveFile;
		SoundBuffer* buffer;
		Sound* sound;
};

/** @} */

#endif