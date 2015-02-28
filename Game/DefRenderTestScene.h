#ifndef __DEFRENDERTESTSCENE_H__
#define __DEFRENDERTESTSCENE_H__

#include "FrameBufferObjects.h"
#include "Scene.h"
#include "settings.h"
#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include <Texture.h>
#include "Geometry.h"
#include "GeometryObject.h"
#include "Player.h"

/// %Scene used to test the deferred rendering.
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
		void bindGeometry(int width, int height);


		/// Render the geometry in the scene.
		/**
		* @param width Width of the context.
		* @param height Height of the context.
		*/
		void render(int width, int height);

	private:
		void bindTriangleData();
		void bindDeferredQuad();

		FrameBufferObjects* multipleRenderTargets;

		// Shaders geometry pass
		Geometry* geometry;
		GeometryObject* geometryObject;
		Shader* vertexShader;
		Shader* geometryShader;
		Shader* fragmentShader;
		ShaderProgram* shaderProgram;

		// Shaders lighting pass
		Shader* deferredVertexShader;
		Shader* deferredFragmentShader;
		ShaderProgram* deferredShaderProgram;

		// Misc
		int state; // 0 == deferred render, 1== display textures.
		Texture* texture;
		Player* player;

		// Vertex buffer geometry
		GLuint vertexBuffer = 0;
		GLuint vertexAttribute = 0;

		// Index buffer geometry
		GLuint indexBuffer = 0;
		unsigned int indexCount = 0;
		int vertexCount = 0;
};

#endif