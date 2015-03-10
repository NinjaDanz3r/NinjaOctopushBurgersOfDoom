#ifndef __TEXTUREPREVIEW_H__
#define __TEXTUREPREVIEW_H__

#include "Preview.h"
#include <ShaderProgram.h>
#include <Texture.h>
#include <glm/glm.hpp>

/// Previews a texture.
class TexturePreview : public Preview {
	public:
		/// Create new texture preview.
		/**
		 * @param shaderProgram Shader program to render with.
		 */
		TexturePreview(ShaderProgram* shaderProgram);

		/// Destructor.
		~TexturePreview();

		/// Set texture to preview.
		/**
		 * @param texture Texture to preview.
		 */
		void setTexture(Texture* texture);

		/// Render the texture.
		/**
		* @param width Width of the render context.
		* @param height Height of the render context.
		*/
		void render(int width, int height) const;

	private:
		void bindQuad();

		Texture* texture = nullptr;
		ShaderProgram* shaderProgram;

		// Full screen quad.
		static const glm::vec2 vertices[6];

		// Vertex buffer
		GLuint vertexBuffer;
		GLuint vertexAttribute;
		unsigned int vertexCount;
};

#endif