#include <GL/glew.h>

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "Game.h"
#include "settings.h"
#include "input.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>

// Handles errors by printing them to the standard error stream.
static void errorCallback(int error, const char* description) {
	fputs(description, stderr);
}

// Handles key events.
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

// Main game function. Contains the main loop.
int main() {
	input::init();
	settings::load("settings.ini");

	#if defined(_WIN32) || defined(WIN32)
	if (settings::freeConsole())
		FreeConsole();
	#endif
	
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

	settings::save("settings.ini");

	_CrtDumpMemoryLeaks();

	exit(EXIT_SUCCESS);
}