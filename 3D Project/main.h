#ifndef __MAIN_H__
#define __MAIN_H__

#define GLFW_DLL
#include <GLFW/glfw3.h>

// Main game function. Contains the main loop.
int main();

// Setup debug functionality (like logging).
void setupDebug();

// Create the main game window.
GLFWwindow* createWindow();

// Handles errors by printing them to the standard error stream.
void errorCallback(int error, const char* description);

// Handles key events.
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Handles OpenGL debug messages.
void APIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

#endif