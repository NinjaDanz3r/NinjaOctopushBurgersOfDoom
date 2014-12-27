#include "Game.h"
#include "TestScene.h"

Game::Game(GLFWwindow* window) {
	this->window = window;
	currentScene = new TestScene();
	lastTime = glfwGetTime();
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
	} else {
		if (status->command == Scene::SceneEnd::NEW_SCENE) {
			delete currentScene;
			currentScene = status->nextScene;
		}

		if (status->command == Scene::SceneEnd::QUIT)
			glfwSetWindowShouldClose(window, GL_TRUE);

		delete status;
	}

	lastTime = glfwGetTime();
}