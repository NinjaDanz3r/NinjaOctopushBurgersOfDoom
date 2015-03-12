#include "Game.h"
#include "TestScene.h"

#include "ParticleScene.h"
#include "TerrainScene.h"
#include "TestScene.h"
#include "AudioScene.h"
#include "PickingScene.h"
#include "FrustumScene.h"

#include "input.h"
#include "settings.h"

#include <stdio.h>

static std::map<std::string, Scene*(*)()>* sceneMap;

Game::Game(GLFWwindow* window, const char* sceneName) {
	this->window = window;
	input::setWindow(window);
	assignKeyboardBindings();
	soundSystem = new SoundSystem();

	sceneMap = new std::map< std::string, Scene*(*)()>();
	setSceneMap();
	setScene(sceneName);

	lastTime = glfwGetTime();
	prevFPSTime = lastTime;

	glEnable(GL_DEPTH_TEST);
}

Game::~Game() {
	delete currentScene;
	delete soundSystem;
	delete sceneMap;
}

void Game::update() {
	int width, height;
	double deltaTime;
	glfwGetFramebufferSize(window, &width, &height);
	deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
	input::update();

	Scene::SceneEnd* status = currentScene->update(deltaTime);

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

	setWindowTitle();

	//if (settings::showFPS() || settings::showCursorCoordinates)
	//	setWindowFPS();
}

void Game::setWindowTitle()
{
	frames++;

	if (glfwGetTime() - prevFPSTime >= 1.0) {
		char title[256];
		title[255] = '\0';
		int len = 0;
		len += sprintf(title, "Super Awesome 3D Project - ");
		if (settings::showFPS())
			len += sprintf(title + len, "[FPS: %i] - ", frames);
		if (settings::showCursorCoordinates())
			len += sprintf(title + len, "[CursorXY: %.f %.f] - ", input::cursorX(), input::cursorY());

		glfwSetWindowTitle(window, title);

		frames = 0;
		prevFPSTime += 1.0;
	}
}

void Game::setWindowFPS() {
	frames++;

	if (glfwGetTime() - prevFPSTime >= 1.0) {
		char title[256];
		title[255] = '\0';
		sprintf(title, "Super Awesome 3D Project - [FPS: %i] - [CursorsXY: %.f , %.f]", frames, input::cursorX() , input::cursorY() );

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
	input::assignKeyboard(input::CHANGE_RENDER_STATE, GLFW_KEY_F1);
}

template<typename T> Scene * createInstance() {
	return new T;
}

void Game::setSceneMap() {
	(*sceneMap)["default"] = &createInstance<TestScene>;
	(*sceneMap)["test"] = &createInstance<TestScene>;
	(*sceneMap)["audio"] = &createInstance<AudioScene>;
	(*sceneMap)["particle"] = &createInstance<ParticleScene>;
	(*sceneMap)["terrain"] = &createInstance<TerrainScene>;
	(*sceneMap)["picking"] = &createInstance<PickingScene>;
	(*sceneMap)["frustum"] = &createInstance<FrustumScene>;
}

void Game::setScene(const char* sceneName){
	std::map<std::string, Scene*(*)()>::const_iterator itFound;
	itFound = sceneMap->find(sceneName); 
	if (itFound != sceneMap->end())
		currentScene = (*sceneMap)[sceneName]();
	else
		currentScene = (*sceneMap)["default"]();
}

