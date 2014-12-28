#ifndef __INPUT_H__
#define __INPUT_H__

#define GLFW_DLL
#include <GLFW/glfw3.h>

namespace input {
	// Button codes.
	enum Button {
		FORWARD = 0,
		BACKWARD,
		LEFT,
		RIGHT,
		BUTTONS
	};

	// Initialize the input module.
	void init();

	// Free the input module.
	void free();

	// Set window for which to retrieve input.
	void setWindow(GLFWwindow* window);

	// Update input.
	void update();

	// Assign a keyboard key to a button.
	void assignKeyboard(Button button, int key);

	// Gets whether a button is currently down.
	bool pressed(Button button);

	// Get the cursor's x-position in the window.
	double cursorX();

	// Get the cursor's y-position in the window.
	double cursorY();

	// Get the cursor's x-position relative to the center of the window.
	double cursorCenterX();

	// Get the cursor's y-position relative to the center of the window.
	double cursorCenterY();

	// Centers the cursor to the middle of the window.
	void centerCursor();
}

#endif