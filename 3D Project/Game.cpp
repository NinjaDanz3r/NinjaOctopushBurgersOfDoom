#include "Game.h"
#include "TestScene.h"
#include "DefRenderTestScene.h"
#include "AudioScene.h"
#include "input.h"

#include <stdio.h>

Game::Game(GLFWwindow* window) {
	this->window = window;
	input::setWindow(window);
	assignKeyboardBindings();

	currentScene = new DefRenderTestScene(); //new AudioScene();
	lastTime = glfwGetTime();
	prevFPSTime = lastTime;

	glEnable(GL_DEPTH_TEST);
}

Game::~Game() {
	delete currentScene;
	input::free();
}

void Game::update() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	input::update();

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

void Game::assignKeyboardBindings() {
	input::assignKeyboard(input::FORWARD, GLFW_KEY_W);
	input::assignKeyboard(input::BACKWARD, GLFW_KEY_S);
	input::assignKeyboard(input::LEFT, GLFW_KEY_A);
	input::assignKeyboard(input::RIGHT, GLFW_KEY_D);
}