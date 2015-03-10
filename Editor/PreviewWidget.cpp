#include "PreviewWidget.h"

#include <Texture2D.h>

PreviewWidget::PreviewWidget(QWidget* parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
	
}

PreviewWidget::~PreviewWidget() {
	delete _texturePreview;
}

TexturePreview* PreviewWidget::texturePreview() const {
	return _texturePreview;
}

void PreviewWidget::initializeGL() {
	glewInit();
	glEnable(GL_DEPTH_TEST);

	_texturePreview = new TexturePreview();
	activePreview = _texturePreview;
}

void PreviewWidget::paintGL() {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	activePreview->render(width, height);
}

void PreviewWidget::resizeGL(int width, int height) {
	this->width = width;
	this->height = height;
}