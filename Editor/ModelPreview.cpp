#include "ModelPreview.h"

ModelPreview::ModelPreview() {
	vertexShader = new Shader("showModel_vertex.glsl", GL_VERTEX_SHADER);
	fragmentShader = new Shader("showModel_fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = new ShaderProgram({ vertexShader, fragmentShader });
}

ModelPreview::~ModelPreview() {
	delete shaderProgram;
	delete vertexShader;
	delete fragmentShader;
}

void ModelPreview::setModel(Model* model) {
	this->model = model;
}

void ModelPreview::render(int width, int height) const {
	if (model != nullptr) {
		shaderProgram->use();

		glBindVertexArray(model->vertexArray());

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, model->indexCount(), GL_UNSIGNED_INT, (void*)0);
	}
}