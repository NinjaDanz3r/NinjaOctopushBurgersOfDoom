#include <GL/glew.h>

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

#include "main.h"
#include "Game.h"
#include "settings.h"
#include "input.h"
#include "util.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	input::init();
	settings::load(util::savePath("settings.ini").c_str());

	setupDebug();
	util::logWithTime("Game started");
	
	GLFWwindow* window = createWindow();
	glfwMakeContextCurrent(window);

	glewInit();

	glfwSetKeyCallback(window, keyCallback);

	Game* game = new Game(window);
	while (!glfwWindowShouldClose(window)) {
		game->update();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete game;

	glfwDestroyWindow(window);
	glfwTerminate();

	settings::save(util::savePath("settings.ini").c_str());

	util::logWithTime("Game ended");

	_CrtDumpMemoryLeaks();

	exit(EXIT_SUCCESS);
}

void setupDebug() {
#if defined(_WIN32) || defined(WIN32)
	if (!settings::showConsole())
		FreeConsole();
#endif

	if (settings::logging())
		freopen(util::savePath("log.txt").c_str(), "a", stderr);
}

GLFWwindow* createWindow() {
	GLFWwindow* window;

	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	if (settings::borderless())
		glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWmonitor* monitor = settings::fullscreen() ? glfwGetPrimaryMonitor() : nullptr;
	window = glfwCreateWindow(settings::displayWidth(), settings::displayHeight(), "Super Awesome 3D Project", monitor, nullptr);
	if (!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	if (!settings::showMouseCursor())
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return window;
}

static void errorCallback(int error, const char* description) {
	fputs(description, stderr);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}