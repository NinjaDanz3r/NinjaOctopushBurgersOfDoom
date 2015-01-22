#ifndef __AUDIOSCENE_H__
#define __AUDIOSCENE_H__

#include "Scene.h"
#include "Shaders.h"
#include "Texture.h"
#include "Geometry.h"
#include "Player.h"
#include "WaveFile.h"
#include "SoundBuffer.h"
#include "Sound.h"

// Test scene. Used to test things.
class AudioScene : public Scene {
	public:
		// Constructor
		AudioScene();

		// Destructor
		~AudioScene();

		// Updates the scene.
		SceneEnd* update(double time);

		// Renders the scene.
		void render(int width, int height);

	private:
		void bindTriangleData();

		Shaders* shaders;
		Texture* texture;
		Geometry* geometry;
		Player* player;

		// Vertex buffer.
		GLuint vertexBuffer = 0;
		GLuint vertexAttribute = 0;
		unsigned short vertexCount = 0;

		// Index buffer.
		GLuint indexBuffer = 0;
		unsigned int indexCount = 0;

		// Audio
		WaveFile* waveFile;
		SoundBuffer* buffer;
		Sound* sound;
};

#endif