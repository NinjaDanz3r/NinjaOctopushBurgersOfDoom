#ifndef __SETTINGS_H__
#define __SETTINGS_H__
#include <string>

/// Handles various settings that the user can modify.
/**
 * Settings are stored in util::savePath("settings.ini").
 */
namespace settings {
	/// Initialize the settings module.
	/**
	* Needs to be called before all other functions.
	*/
	void init();

	/// Free the input module.
	/**
	* Should not be called twice.
	*/
	void free();

	/// Load settings from an ini file.
	/**
	 * Settings are given default values if file can not be found or does not contain the corresponding setting.
	 * @param filename Filename (relative or absolute)
	 */
	void load(const char* filename);

	/// Save the settings to an ini file.
	/**
	 * Creates the file if it does not already exist.
	 * @param filename Filename (relative or absolute)
	 */
	void save(const char* filename);

	/// Get the display width.
	/**
	 * Default value: 640.
	 * @return Display width
	 */
	int displayWidth();

	/// Get the display height.
	/**
	 * Default value: 480.
	 *  @return Display height in pixels
	 */
	int displayHeight();

	/// Set the display size.
	/**
	 * Set the window size (if run in window) or resolution (if run in fullscreen).
	 * @param width Display width in pixels.
	 * @param height Display height in pixels.
	 */
	void setDisplaySize(int width, int height);

	/// Get whether we should render in fullscreen.
	/**
	 * Default false.
	 * @return Whether the game should start in fullscreen mode
	 */
	bool fullscreen();

	/// Set whether we should render in fullscreen.
	/**
	 * @param fullscreen Whether the game should start in fullscreen mode.
	 */
	void setFullscreen(bool fullscreen);

	/// Get whether window should be borderless.
	/**
	 * Default false.
	 * Only applies when running in windowed mode.
	 * @return Whether window should be borderless
	 */
	bool borderless();

	/// Set whether window should be borderless.
	/**
	* Only applies when running in windowed mode.
	* @param borderless Whether window should be borderless
	*/
	void setBorderless(bool borderless);

	/// Get mouse sensitivity.
	/**
	 * Default value: 0.5.
	 * @return Mouse sensitivity (0.0 - 1.0)
	 */
	float mouseSensitivity();

	/// Set mouse sensitivity. (0-1)
	/**
	 * @param sensitivity Mouse sensitivity (0.0  1.0).
	 */
	void setMouseSensitivity(float sensitivity);

	/// Get field of view.
	/**
	 * Default value: 45.0.
	 * @return Field of view (0.0 - 180.0)
	 */
	float fieldOfView();

	/// Set field of view.
	/**
	 * @param fieldOfView Field of view (0.0 - 180.0)
	 */
	void setFieldOfView(float fieldOfView);

	/// Get whether to show the console window.
	/**
	 * Default false.
	 * Only works on Windows.
	 * @return Whether to show the console window
	 */
	bool showConsole();

	/// Set whether to show the console window.
	/**
	 * Only works on Windows.
	 * @param show Whether to show the console window.
	 */
	void setShowConsole(bool show);

	/// Get whether write to a log file.
	/**
	 * Default false.
	 * @return Whether write to a log file
	 * @see util::savePath for where log file is saved.
	 */
	bool logging();

	/// Set whether to write to a log file.
	/**
	 * @param logging Whether to write to a log file.
	 * @see util::savePath for where log file is saved.
	 */
	void setLogging(bool logging);

	/// Get whether to show the mouse cursor.
	/**
	 * Default false.
	 * @return Whether to show the mouse cursor
	 */
	bool showMouseCursor();

	/// Set whether to show the mouse cursor.
	/**
	 * @param show Whether to show the mouse cursor.
	 */
	void setShowMouseCursor(bool show);

	/// Get whether mouse cursor should be centered each frame.
	/**
	 * Necessary for good first person movement.
	 * Default true.
	 * @return Whether mouse cursor should be centered
	 */
	bool centerMouseCursor();

	/// Set whether mouse cursor should be centered each frame.
	/**
	 * @param center Whether mouse cursor should be centered.
	 */
	void setCenterMouseCursor(bool center);

	/// Get whether to show frames per second in window title.
	/**
	 * Default true.
	 * @return Whether to show FPS
	 */
	bool showFPS();

	/// Set whether to show frames per second in window title.
	/**
	 * @param Set whether to show FPS.
	 */
	void setShowFPS(bool show);

	/// Get whether to show cursor X,Y in window title.
	/**
	* Default true.
	* @return Whether to show cursor coordinates
	*/
	bool showCursorCoordinates();

	/// Set whether to show frames per second in window title.
	/**
	* @param set Whether to show cursor coordinates.
	*/
	void setShowCursorCoordinates(bool show);

	/// Get whether an OpenGL Debug Context should be created.
	/**
	 * Default false.
	 * @return Whether debug context should be created
	 * @see <a href="https://www.opengl.org/wiki/Debug_Output">OpenGL Debug Output</a>
	 */
	bool debugContext();

	/// Set whether an OpenGL Debug Context should be created.
	/**
	 * @param debug Whether debug context should be created.
	 * @see <a href="https://www.opengl.org/wiki/Debug_Output">OpenGL Debug Output</a>
	 */
	void setDebugContext(bool debug);

	/// Get the name of the starting scene.
	/**
	* @return The name of the scene to load
	*/
	std::string startingScene();

	/// Set the name of the starting scene.
	/**
	* @param startingScene Name of the starting scene.
	*/
	void setStartingScene(std::string startingScene);
}

#endif