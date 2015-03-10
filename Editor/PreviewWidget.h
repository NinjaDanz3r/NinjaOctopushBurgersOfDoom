#ifndef __PREVIEWWIDGET_H__
#define __PREVIEWWIDGET_H__

#include <gl/glew.h>
#include <gl/GL.h>

#include <QGLWidget>
#include <Shader.h>
#include <ShaderProgram.h>
#include <Texture.h>
#include "Preview.h"
#include "TexturePreview.h"

/** @ingroup editor
 * @{
 */

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

		/// Get texture preview.
		/**
		 * @return The texture preview
		 */
		TexturePreview* texturePreview() const;

	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height);

	private:
		int width, height;

		// Previews
		Preview* activePreview;
		TexturePreview* _texturePreview;

		// Shaders
		Shader* vertexShader;
		Shader* fragmentShader;
		ShaderProgram* shaderProgram;
};

/** @} */

#endif