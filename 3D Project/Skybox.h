#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "CubeMapTexture.h"
#include "Camera.h"
#include "ShaderProgram.h"

/// A skybox.
/**
 * A box rendered behind all other objects and which moves with the player, creating the illusion that it is infinitely far away.
 * Useful for making game worlds appear larger than they are.
 */
class Skybox {
	public:
		/// A vertex in the skybox.
		struct Vertex {
			/// X-position.
			float x;
			/// Y-position.
			float y;
			/// Z-position.
			float z;
		};

		/// Create new skybox from a cubemap texture.
		/**
		 * @param texture The cubemap texture to apply to the faces of the box.
		 */
		Skybox(const CubeMapTexture* texture);

		/// Destructor
		/**
		 * Free all allocated resources.
		 */
		~Skybox();

		/// Render skybox.
		/**
		 * @param width Width of the context.
		 * @param height Height of the context.
		 * @param camera Camera through which to render (only orientation is used, not translation).
		 */
		void render(int width, int height, const Camera* camera);

	private:
		void bindData();

		static Vertex vertices[8];
		static unsigned int indices[36];

		const CubeMapTexture* texture;

		// Shaders
		Shader* vertexShader;
		Shader* fragmentShader;
		ShaderProgram* shaderProgram;

		// Vertex buffer
		GLuint vertexBuffer = 0;
		GLuint vertexAttribute = 0;

		// Index buffer.
		GLuint indexBuffer = 0;
};

#endif