#ifndef __PREVIEWWIDGET_H__
#define __PREVIEWWIDGET_H__

#include <QGLWidget>

class PreviewWidget : public QGLWidget {
	Q_OBJECT

	public:
		explicit PreviewWidget(QWidget* parent = nullptr);
};

#endif