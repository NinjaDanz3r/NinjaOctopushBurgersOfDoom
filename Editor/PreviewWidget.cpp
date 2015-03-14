#include "PreviewWidget.h"
#include "Preview.h"
#include "TexturePreview.h"
#include "ModelPreview.h"

#include <Texture2D.h>

PreviewWidget::PreviewWidget(QWidget* parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {

}

PreviewWidget::~PreviewWidget() {
	delete _texturePreview;
	delete _modelPreview;
	activePreview = nullptr;
}

TexturePreview* PreviewWidget::texturePreview() const {
	return _texturePreview;
}

ModelPreview* PreviewWidget::modelPreview() const {
	return _modelPreview;
}

void PreviewWidget::setPreview(Preview* preview) {
	activePreview = preview;
}

void PreviewWidget::initializeGL() {
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	_texturePreview = new TexturePreview();
	_modelPreview = new ModelPreview();

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