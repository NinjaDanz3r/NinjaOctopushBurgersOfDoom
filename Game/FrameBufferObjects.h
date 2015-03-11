#ifndef __FRAMEBUFFEROBJECTS_H__
#define __FRAMEBUFFEROBJECTS_H__

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include "ShaderProgram.h"
#include "Camera.h"

/** @ingroup game
 * @{
 */

/// Holds the frame buffers used for deferred rendering.
class FrameBufferObjects {
	public:
		/// The different buffer types.
		enum TEXTURE_TYPE {
			POSITION, ///< Position
			DIFFUSE, ///< Diffuse texture
			NORMAL, ///< Normals
			SPECULAR, ///< Specular
			NUM_TEXTURES ///< Total number of textures (excluding depth buffer)
		};

		/// Constructor
		/**
		 * @param shaderProgram Shader program with which to combine the different buffers into the final image.
		 * @param width Width of the context.
		 * @param height Height of the context.
		 */
		FrameBufferObjects(ShaderProgram* shaderProgram, unsigned int width, unsigned int height);

		/// Destructor
		/**
		 * Free allocated resources.
		 */
		~FrameBufferObjects();

		/// Get texture.
		/**
		 * @param textureType The type of texture to get.
		 * @return The texture identifier
		 */
		GLuint texture(TEXTURE_TYPE textureType) const;

		/// Enable frame buffer object for writing.
		void bindForWriting();

		/// Enable frame buffer object for reading.
		void bindForReading();

		/// Enable frame buffer object for reading textures.
		void bindForTexReading();

		/// Set buffer to read from.
		/**
		 * @param textureType Texture type of the buffer to read from.
		 */
		void setReadBuffer(TEXTURE_TYPE textureType);

		/// Render the content of diffuse, position and normal textures
		/**
		 * @param width Width of the context.
		 * @param height Height of the context.
		 */
		void showTextures(int width, int height);

		/// Render the lighting in the scene.
		/**
		 * @param camera Camera to use.
		 * @param width Width of the context.
		 * @param height Height of the context.
		 */
		void render(Camera* camera, int width, int height);

	private:
		static void attachTexture(GLuint texture, unsigned int width, unsigned int height, GLenum attachment);
		void bindLighting(Camera* camera, int width, int height);
		void bindQuad();

		GLuint mTextures[NUM_TEXTURES];

		GLuint fbo;
		GLuint depthHandle;

		ShaderProgram* shaderProgram;

		unsigned int width;
		unsigned int height;

		// Full screen quad
		static const glm::vec2 vertices[4];
		static const unsigned int indices[6];

		// Vertex buffer
		GLuint vertexBuffer;
		GLuint vertexAttribute;
		unsigned int vertexCount;

		// Index buffer
		GLuint indexBuffer;
		unsigned int indexCount;
};

/** @} */

#endif
