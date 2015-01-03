#include "settings.h"
#include <SimpleIni.h>

namespace settings {
	float _mouseSensitivity;

	int _displayWidth = 640, _displayHeight = 480;
	bool _fullscreen;
	bool _borderless;
	float _fieldOfView;

	bool _freeConsole;

	void load(const char* filename) {
		CSimpleIniA ini;
		ini.SetUnicode();
		ini.LoadFile(filename);

		_mouseSensitivity = static_cast<float>(ini.GetDoubleValue("Controls", "Mouse Sensitivity", 0.5f));
		_displayWidth = ini.GetLongValue("Graphics", "Width", 640);
		_displayHeight = ini.GetLongValue("Graphics", "Height", 480);
		_fullscreen = ini.GetBoolValue("Graphics", "Fullscreen");
		_borderless = ini.GetBoolValue("Graphics", "Borderless");
		_fieldOfView = static_cast<float>(ini.GetDoubleValue("Graphics", "Field of View", 45.f));
		_freeConsole = ini.GetBoolValue("Debug", "freeConsole", true);
	}

	void save(const char* filename) {
		CSimpleIniA ini;
		ini.SetUnicode();

		ini.SetDoubleValue("Controls", "Mouse Sensitivity", _mouseSensitivity);
		ini.SetLongValue("Graphics", "Width", _displayWidth);
		ini.SetLongValue("Graphics", "Height", _displayHeight);
		ini.SetBoolValue("Graphics", "Fullscreen", _fullscreen);
		ini.SetBoolValue("Graphics", "Borderless", _borderless);
		ini.SetDoubleValue("Graphics", "Field of View", _fieldOfView);
		ini.SetBoolValue("Debug", "Free Console", _freeConsole);

		SI_Error rc = ini.SaveFile(filename);
		if (rc < 0)
			fputs("Couldn't save settings", stderr);
	}

	int displayWidth() {
		return _displayWidth;
	}

	int displayHeight() {
		return _displayHeight;
	}

	void setDisplaySize(int width, int height) {
		_displayWidth = width;
		_displayHeight = height;
	}

	bool fullscreen() {
		return _fullscreen;
	}

	void setFullscreen(bool fullscreen) {
		_fullscreen = fullscreen;
	}

	bool borderless() {
		return _borderless;
	}

	void setBorderless(bool borderless) {
		_borderless = borderless;
	}

	float mouseSensitivity() {
		return _mouseSensitivity;
	}

	void setMouseSensitivity(float sensitivity) {
		_mouseSensitivity = sensitivity;
		if (_mouseSensitivity < 0.f)
			_mouseSensitivity = 0.f;
		if (_mouseSensitivity > 1.f)
			_mouseSensitivity = 1.f;
	}

	float fieldOfView() {
		return _fieldOfView;
	}

	void setFieldOfView(float fieldOfView) {
		_fieldOfView = fieldOfView;
		if (_mouseSensitivity < 0.f)
			_mouseSensitivity = 0.f;
		if (_mouseSensitivity > 180.f)
			_mouseSensitivity = 180.f;
	}

	bool freeConsole() {
		return _freeConsole;
	}

	void setFreeConsole(bool free) {
		_freeConsole = free;
	}
}