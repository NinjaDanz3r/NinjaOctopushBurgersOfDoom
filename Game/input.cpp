#include "input.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <vector>

namespace input {
	GLFWwindow* _window;
	std::vector<int>* keyboardBindings;
	bool buttonDown[BUTTONS];
	bool buttonTriggered[BUTTONS];
	bool buttonReleased[BUTTONS];

	void init() {
		keyboardBindings = new std::vector<int>[BUTTONS];
	}

	void free() {
		delete[] keyboardBindings;
	}

	void setWindow(GLFWwindow* window) {
		_window = window;
	}

	void update() {
		for (int button = 0; button < BUTTONS; button++) {
			bool pressed = false;
			for (auto &key : keyboardBindings[button]) {
				if (glfwGetKey(_window, key) == GLFW_PRESS)
					pressed = true;
			}

			buttonTriggered[button] = !buttonDown[button] && pressed;
			buttonReleased[button] = buttonDown[button] && !pressed;
			buttonDown[button] = pressed;
		}
	}

	void assignKeyboard(Button button, int key) {
		keyboardBindings[button].push_back(key);
	}

	bool pressed(Button button) {
		return buttonDown[button];
	}

	bool triggered(Button button) {
		return buttonTriggered[button];
	}

	bool released(Button button) {
		return buttonReleased[button];
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