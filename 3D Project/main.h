#ifndef __MAIN_H__
#define __MAIN_H__

#define GLFW_DLL
#include <GLFW/glfw3.h>

// Main game function. Contains the main loop.
int main();

// Create the main game window.
GLFWwindow* createWindow();

// Handles errors by printing them to the standard error stream.
static void errorCallback(int error, const char* description);

// Handles key events.
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif