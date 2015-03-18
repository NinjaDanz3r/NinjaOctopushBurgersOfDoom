#ifndef __DEFRENDERTESTSCENE_H__
#define __DEFRENDERTESTSCENE_H__

#include "FrameBufferObjects.h"
#include "Scene.h"

class FrameBufferObjects;
class ShadowMapping;
class Geometry;
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

		/// Vertex in full screen quad
		struct RenderQuad {
			//x-pos
			float x;
			//y-pos
			float y;
		};

		struct ShadowBox {
			glm::vec3 position;
		};

		/// Update the scene.
		/**
		* @param time Time since last frame (in seconds).
		* @return SceneEnd-struct defining what to do next. nullptr if nothing should be done
		*/
		SceneEnd* update(double time);
		void bindGeometry(int width, int height, Geometry* geometry);
		void bindLighting(int width, int height);


		/// Render the geometry in the scene.
		/**
		* @param width Width of the context.
		* @param height Height of the context.
		*/
		void render(int width, int height);

		/// Render the lighting in the scene.
		/**
		* @param width Width of the context.
		* @param height Height of the context.
		*/
		void deferredRender(int width, int height);

		/// Render the content of diffuse, position and normal textures
		/**
		* @param width Width of the context.
		* @param height Height of the context.
		*/
		void showTex(int width, int height);
		void shadowRender(int width, int height);
		void bindShadowGeometry();
	private:
		void bindTriangleData();
		void bindDeferredQuad();
		void bindGroundGeometry();

		GLuint shadowID;
		GLuint diffuseID;
		GLuint positionID;
		GLuint normalID;

		FrameBufferObjects* multiplerendertargets;
		ShadowMapping* shadowMap;
		ShadowBox *verticesShadowBox;

		// Shaders geometry pass
		Geometry* geometryGround;
		Geometry* geometry;
		Shader* vertexShader;
		Shader* geometryShader;
		Shader* fragmentShader;
		ShaderProgram* shaderProgram;

		// Shaders lighting pass
		Shader* secondVertexShader;
		Shader* secondFragmentShader;
		ShaderProgram* secondShaderProgram;

		// Shaders lighting pass
		Shader* shadowVertexShader;
		Shader* shadowFragmentShader;
		ShaderProgram* shadowShaderProgram;

		// Misc
		int state; //0 == deferred render, 1== display textures.
		Texture* texture;
		Player* player;
		GLuint halfWidth;
		GLuint halfHeight;

		// Vertex buffer geometry
		GLuint groundVertexBuffer = 0;
		GLuint groundVertexAttribute = 0;

		// Vertex buffer shadow geometry
		GLuint shadowVertexBuffer = 0;
		GLuint shadowVertexAttribute = 0;

		//Index buffer geometry
		GLuint shadowIndexBuffer = 0;

		// Vertex buffer geometry
		GLuint gVertexBuffer = 0;
		GLuint gVertexAttribute = 0;

		//Index buffer geometry
		GLuint gIndexBuffer = 0;
		unsigned int indexCount = 0;
		int vertexCount = 0;

		// Vertex buffer lighting
		GLuint qVertexBuffer = 0;
		GLuint qVertexAttribute = 0;

		// Index buffer lighting
		GLuint qIndexBuffer = 0;
		unsigned int qIndexCount = 0;
		int qVertexCount = 0;

		// Full screen quad
		static RenderQuad vertices[4];
		static unsigned int indices[6];
};
#endif
