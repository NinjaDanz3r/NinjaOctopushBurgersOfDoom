#include <gl/glew.h>
#include <gl/GL.h>

#include <GLFW\glfw3.h>

#include "TestScene.h"

TestScene::TestScene() {

}

TestScene::~TestScene() {

}

Scene::SceneEnd* TestScene::update(double time) {
	rotation += (float)time * 50.f;

	if (rotation > 270.f)
		return new Scene::SceneEnd(Scene::SceneEnd::NEW_SCENE, new TestScene());

	return nullptr;
}

void TestScene::render(int width, int height) {
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = width / (float)height;
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef(rotation, 0.f, 0.f, 1.f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
}