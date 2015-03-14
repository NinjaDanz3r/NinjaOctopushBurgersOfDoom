#ifndef __MODELPREVIEW_H__
#define __MODELPREVIEW_H__

#include "Preview.h"
#include <glm/glm.hpp>

class Model;
class Shader;
class ShaderProgram;

/** @ingroup editor
 * @{
 */

/// Previews a model.
class ModelPreview : public Preview {
	public:
		/// Create new model preview.
		ModelPreview();

		/// Destructor.
		~ModelPreview();

		/// Set model to preview.
		/**
		 * @param model Model to preview.
		 */
		void setModel(Model* model);

		/// Render the texture.
		/**
		* @param width Width of the render context.
		* @param height Height of the render context.
		*/
		void render(int width, int height) const;

	private:
		Model* model = nullptr;
		
		// Shaders
		Shader* vertexShader;
		Shader* fragmentShader;
		ShaderProgram* shaderProgram;
};

/** @} */

#endif