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
#include <time.h>

int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	input::init();
	settings::load(util::savePath("settings.ini").c_str());

	setupDebug();
	util::logWithTime("Game started");
	
	GLFWwindow* window = createWindow();
	glfwMakeContextCurrent(window);

	glewInit();
	std::string test = settings::startingScene();
	glfwSetKeyCallback(window, keyCallback);
	if (settings::debugContext())
		glDebugMessageCallback(debugMessageCallback, nullptr);

	Game* game = new Game(window, settings::startingScene().c_str());
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
	if (settings::debugContext())
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
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

void errorCallback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void APIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	switch (source) {
	case GL_DEBUG_SOURCE_API:
		fputs("Open GL API", stderr);
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		fputs("Window System", stderr);
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		fputs("Shader Compiler", stderr);
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		fputs("Application", stderr);
		break;
	default:
		fputs("Other", stderr);
	}

	fputs(": ", stderr);

	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		fputs("Error", stderr);
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		fputs("Deprecated Behavior", stderr);
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		fputs("Undefined Behavior", stderr);
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		fputs("Portability", stderr);
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		fputs("Performance", stderr);
		break;
	case GL_DEBUG_TYPE_MARKER:
		fputs("Marker", stderr);
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		fputs("Push Group", stderr);
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		fputs("Pop Group", stderr);
		break;
	default:
		fputs("Other", stderr);
	}

	fputs(" (", stderr);

	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:
		fputs("High Priority", stderr);
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		fputs("Medium Priority", stderr);
		break;
	case GL_DEBUG_SEVERITY_LOW:
		fputs("Low Priority", stderr);
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		fputs("Notification", stderr);
		break;
	}

	fputs("):\n", stderr);

	fputs(message, stderr);
	fputs("\n\n", stderr);

	fflush(stderr);
}