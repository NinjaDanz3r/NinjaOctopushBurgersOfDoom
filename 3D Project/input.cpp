#include "input.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>

namespace input {
	GLFWwindow* _window;

	void setWindow(GLFWwindow* window) {
		_window = window;
	}

	bool pressed(Button button) {
		return glfwGetKey(_window, GLFW_KEY_W) == GLFW_KEY_DOWN;
	}

	double cursorX() {
		double x, y;
		glfwGetCursorPos(_window, &x, &y);
		return x;
	}

	double cursorY() {
		double x, y;
		glfwGetCursorPos(_window, &x, &y);
		return y;
	}

	double cursorCenterX() {
		double x, y;
		glfwGetCursorPos(_window, &x, &y);

		int width, height;
		glfwGetFramebufferSize(_window, &width, &height);

		return x - (double)width/2;
	}

	double cursorCenterY() {
		double x, y;
		glfwGetCursorPos(_window, &x, &y);

		int width, height;
		glfwGetFramebufferSize(_window, &width, &height);

		return y - (double)height/2;
	}

	void centerCursor() {
		int width, height;
		glfwGetFramebufferSize(_window, &width, &height);
		glfwSetCursorPos(_window, width/2, height/2);
	}
}