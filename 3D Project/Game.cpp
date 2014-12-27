#include "Game.h"
#include "TestScene.h"

#include <stdio.h>

Game::Game(GLFWwindow* window) {
	this->window = window;
	currentScene = new TestScene();
	lastTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);
}

Game::~Game() {
	delete currentScene;
}

void Game::update() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	Scene::SceneEnd* status = currentScene->update(glfwGetTime() - lastTime);
	if (status == nullptr) {
		currentScene->render(width, height);
	}
	else {
		if (status->command == Scene::SceneEnd::NEW_SCENE) {
			delete currentScene;
			currentScene = status->nextScene;
		}

		if (status->command == Scene::SceneEnd::QUIT)
			glfwSetWindowShouldClose(window, GL_TRUE);

		delete status;
	}

	lastTime = glfwGetTime();
	setWindowFPS();
}

void Game::setWindowFPS() {
	frames++;

	if (glfwGetTime() - prevFPSTime >= 1.0) {
		char title[256];
		title[255] = '\0';

		sprintf(title, "Super Awesome 3D Project - [FPS: %i]", frames);

		glfwSetWindowTitle(window, title);

		frames = 0;
		prevFPSTime += 1.0;
	}
}