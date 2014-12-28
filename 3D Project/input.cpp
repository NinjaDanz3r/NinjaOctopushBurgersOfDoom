#include "input.h"

#include <vector>

namespace input {
	GLFWwindow* _window;
	std::vector<int>* keyboardBindings;
	bool buttonDown[BUTTONS];

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
			buttonDown[button] = false;
			for (auto &key : keyboardBindings[button]) {
				if (glfwGetKey(_window, key) == GLFW_PRESS)
					buttonDown[button] = true;
			}
		}
	}

	void assignKeyboard(Button button, int key) {
		keyboardBindings[button].push_back(key);
	}

	bool pressed(Button button) {
		return buttonDown[button];
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