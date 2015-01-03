#ifndef __SETTINGS_H__
#define __SETTINGS_H__

namespace settings {
	// Load settings from an ini file.
	void load(const char* filename);

	// Save the settings to an ini file.
	void save(const char* filename);

	// Get mouse sensitivity (0-1).
	float mouseSensitivity();

	// Set mouse sensitivity. (0-1)
	void setMouseSensitivity(float sensitivity);

	// Get whether to free console.
	bool freeConsole();

	// Set whether to free console.
	void setFreeConsole(bool free);
}

#endif