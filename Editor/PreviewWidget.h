#ifndef __PREVIEWWIDGET_H__
#define __PREVIEWWIDGET_H__

#include <gl/glew.h>
#include <gl/GL.h>

#include <QGLWidget>
#include <glm/glm.hpp>
#include <Shader.h>
#include <ShaderProgram.h>
#include <Texture.h>

/// Widget that displays a preview of the selected resource.
class PreviewWidget : public QGLWidget {
	Q_OBJECT

	public:
		/// Create new preview widget.
		/**
		 * @param parent Parent widget.
		 */
		explicit PreviewWidget(QWidget* parent = nullptr);

		/// Destructor.
		~PreviewWidget();

	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height);

	private:
		void bindQuad();
		
		int width, height;

		Texture* texture;

		// Shaders
		Shader* vertexShader;
		Shader* fragmentShader;
		ShaderProgram* shaderProgram;

		// Full screen quad.
		static const glm::vec2 vertices[6];

		// Vertex buffer
		GLuint vertexBuffer;
		GLuint vertexAttribute;
		unsigned int vertexCount;
};

#endif