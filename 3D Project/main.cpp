#include <GL/glew.h>

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

#define GLFW_DLL
#include <GLFW/glfw3.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>

#include "Game.h"

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
	GLFWwindow* window;

	#if defined(_WIN32) || defined(WIN32)
	FreeConsole();
	#endif
	
	glfwSetErrorCallback(errorCallback);
	
	glewInit();

	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(640, 480, "Super Awesome 3D Project", NULL, NULL);
	if (!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

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

	_CrtDumpMemoryLeaks();

	exit(EXIT_SUCCESS);
}