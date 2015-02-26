#ifndef __INPUT_H__
#define __INPUT_H__

#define GLFW_DLL
#include <GLFW/glfw3.h>

/// Handles player input.
/**
 * Rather than checking directly for key presses (like 'W'), keys are assigned to more general buttons (eg. 'Forward' to walk forward).
 * This allows keys to be rebound for different keyboard layouts or player preferences.
 */
namespace input {
	/// Button codes.
	enum Button {
		FORWARD = 0, ///< Forward button
		BACKWARD, ///< Backward button
		LEFT, ///< Left button
		RIGHT, ///< Right button
		CHANGE_RENDER_STATE, ///< Change render state button
		BUTTONS ///< Total number of buttons
	};

	/// Initialize the input module.
	/**
	 * Needs to be called before all other functions.
	 */
	void init();

	/// Free the input module.
	/**
	 * Should not be called twice.
	 */
	void free();

	/// Set window for which to retrieve input.
	/**
	 * The window's key callback function is still called even if input is retrieved for it.
	 * @param window The window for which to retrieve input.
	 */
	void setWindow(GLFWwindow* window);

	/// Update input.
	/**
	 * Should be called each frame.
	 */
	void update();

	/// Assign a keyboard key to a button.
	/**
	 * @param button The button to assign a key to.
	 * @param key The <a href="http://www.glfw.org/docs/latest/group__keys.html">keyboard key</a> to assign.
	 */
	void assignKeyboard(Button button, int key);

	/// Gets whether a button is currently down.
	/**
	 * @param button The button to check.
	 * @return Whether the button is down
	 */
	bool pressed(Button button);

	/// Gets whether a button was just pressed.
	/**
	 * Checks whether a button was pressed between the last two calls to update().
	 * @param button The button to check.
	 * @return Whether the button was pressed
	 */
	bool triggered(Button button);

	/// Gets whether a button was just released.
	/**
	 * Checks whether a button was released between the last two calls to update().
	 * @param button The button to check.
	 * @return Whether the button was released
	 */
	bool released(Button button);

	/// Get the cursor's x-position in the window.
	/**
	 * @return The mouse cursor's x-position relative to the window.
	 */
	double cursorX();

	/// Get the cursor's y-position in the window.
	/**
	* @return The mouse cursor's y-position relative to the window.
	*/
	double cursorY();

	/// Get the cursor's x-position relative to the center of the window.
	/**
	* @return The mouse cursor's x-position relative to the center of the window.
	*/
	double cursorCenterX();

	/// Get the cursor's y-position relative to the center of the window.
	/**
	* @return The mouse cursor's y-position relative to the center of the window.
	*/
	double cursorCenterY();

	/// Centers the cursor to the middle of the window.
	void centerCursor();
}

#endif