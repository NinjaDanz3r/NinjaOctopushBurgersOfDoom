#ifndef __SETTINGS_H__
#define __SETTINGS_H__

namespace settings {
	// Load settings from an ini file.
	void load(const char* filename);

	// Save the settings to an ini file.
	void save(const char* filename);

	// Get the display width.
	int displayWidth();

	// Get the display height.
	int displayHeight();

	// Set the display size.
	void setDisplaySize(int width, int height);

	// Get whether we should render in fullscreen.
	bool fullscreen();

	// Set whether we should render in fullscreen.
	void setFullscreen(bool fullscreen);

	// Get whether window should be borderless.
	bool borderless();

	// Set whether window should be borderless.
	void setBorderless();

	// Get mouse sensitivity. (0-1)
	float mouseSensitivity();

	// Set mouse sensitivity. (0-1)
	void setMouseSensitivity(float sensitivity);

	// Get field of view. (0-180)
	float fieldOfView();

	// Set field of view. (0-180)
	void setFieldOfView(float fieldOfView);

	// Get whether to show the console window. Only works on Windows.
	bool showConsole();

	// Set whether to show the console window. Only works on Windows.
	void setShowConsole(bool show);

	// Get whether write to a log file.
	bool logging();

	// Set whether to write to a log file.
	void setLogging(bool logging);

	// Get whether to show the mouse cursor.
	bool showMouseCursor();

	// Set whether to show the mouse cursor.
	void setShowMouseCursor(bool show);

	// Get whether to show frames per second in window title.
	bool showFPS();

	// Set whether to show frames per second in window title.
	void setShowFPS(bool show);
}

#endif