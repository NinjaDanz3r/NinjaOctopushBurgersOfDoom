#ifndef __MAIN_H__
#define __MAIN_H__

#include <GL/glew.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>

/** @ingroup game
 * @{
 */

/// Main game function. Contains the main loop.
int main();

/// Setup debug functionality (like logging).
/**
 * Sets up logging and console if enabled in settings. Log file will be written to util::savePath("log.txt") if logging is enabled; otherwise output will be printed in console (if console is enabled).
 * @see settings
 */
void setupDebug();

/// Create the main game window.
/**
 * Creates the main game window according to settings. Width, height, fullscreen, borderless and whether to create an OpenGL Debug Context can be configured in settings.
 * @return The created window
 * @see <a href="http://www.glfw.org/">GLFW</a>
 * @see settings
 */
GLFWwindow* createWindow();

/// Handles errors by printing them to the standard error stream.
/**
 * GLFW error callback function. Prints incoming errors to the standard error stream (stderr). If logging has been enabled, this is written to util::savePath("log.txt").
 * @param error <a href="http://www.glfw.org/docs/3.0/group__errors.html">GLFW error code</a>.
 * @param description Description text of the error.
 * @see <a href="http://www.glfw.org/docs/3.0/group__error.html">GLFW error handling</a>
 */
void errorCallback(int error, const char* description);

/// Handles key events.
/**
 * GLFW key callback function. Handles incoming key events. Exits the game if Escape is pressed.
 * @param window The window that received the event.
 * @param key The <href="http://www.glfw.org/docs/latest/group__keys.html">keyboard key</a> that was pressed or released. 
 * @param scancode The system-specific scancode of the key. 
 * @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT. 
 * @param mods Bit field describing which <a href="http://www.glfw.org/docs/latest/group__mods.html">modifier keys</a> were held down.
 * @see <a href="http://www.glfw.org/docs/latest/input.html#input_keyboard">GLFW keyboard input</a>
 */
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

/// Handles OpenGL debug messages.
/**
 * OpenGL debug message callback function. Prints debug messages to standard error stream (stderr). If logging has been enabled, this is written to util::savePath("log.txt").
 * @param source The source that produced the message.
 * @param type The type of message.
 * @param id The message's identifier.
 * @param severity The message severity (how important it is).
 * @param length Length of the message.
 * @param message A null-terminated string describing the message.
 * @param userParam User parameters set with glDebugMessageCallback().
 * @see <a href="https://www.opengl.org/wiki/Debug_Output">OpenGL Debug Output</a>
 */
void APIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

/** @} */

#endif