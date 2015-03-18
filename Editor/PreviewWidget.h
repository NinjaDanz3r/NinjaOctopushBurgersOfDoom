#ifndef __PREVIEWWIDGET_H__
#define __PREVIEWWIDGET_H__

#include <gl/glew.h>
#include <QGLWidget>

class Preview;
class TexturePreview;
class ModelPreview;

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

		/// Get model preview.
		/**
		* @return The model preview
		*/
		ModelPreview* modelPreview() const;

		/// Set preview.
		/**
		 * @param preview The preview to use.
		 */
		void setPreview(Preview* preview);

	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height);

	private:
		int width, height;

		// Previews
		Preview* activePreview;
		TexturePreview* _texturePreview;
		ModelPreview* _modelPreview;
};

/** @} */

#endif