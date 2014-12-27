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

	currentScene->update(glfwGetTime() - lastTime);
	currentScene->render(width, height);

	lastTime = glfwGetTime();
}