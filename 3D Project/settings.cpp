#include "settings.h"
#include <SimpleIni.h>
#include <string>

namespace settings {
	float _mouseSensitivity;

	int _displayWidth = 640, _displayHeight = 480;
	bool _fullscreen;
	bool _borderless;
	float _fieldOfView;

	bool _showConsole;
	bool _logging;
	bool _showMouseCursor;
	bool _showFPS;
	bool _debugContext;
	std::string _startingScene;

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
		_showConsole = ini.GetBoolValue("Debug", "Show Console");
		_logging = ini.GetBoolValue("Debug", "Logging");
		_showMouseCursor = ini.GetBoolValue("Debug", "Show Mouse Cursor");
		_showFPS = ini.GetBoolValue("Debug", "Show FPS", true);
		_debugContext = ini.GetBoolValue("Debug", "Debug Context", false);
		_startingScene = ini.GetValue("Debug", "Starting Scene", "default");
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
		ini.SetBoolValue("Debug", "Show Console", _showConsole);
		ini.SetBoolValue("Debug", "Logging", _logging);
		ini.SetBoolValue("Debug", "Show Mouse Cursor", _showMouseCursor);
		ini.SetBoolValue("Debug", "Show FPS", _showFPS);
		ini.SetBoolValue("Debug", "Debug Context", _debugContext);
		ini.SetValue("Debug", "Starting Scene", "default");
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

	bool showConsole() {
		return _showConsole;
	}

	void setShowConsole(bool show) {
		_showConsole = show;
	}

	bool logging() {
		return _logging;
	}

	void setLogging(bool logging) {
		_logging = logging;
	}

	bool showMouseCursor() {
		return _showMouseCursor;
	}

	void setShowMouseCursor(bool show) {
		_showMouseCursor = show;
	}

	bool showFPS() {
		return _showFPS;
	}

	void setShowFPS(bool show) {
		_showFPS = show;
	}

	bool debugContext() {
		return _debugContext;
	}

	void setDebugContext(bool debug) {
		_debugContext = debug;
	}

	std::string startingScene() {
		return _startingScene;
	}

	void setStartingScene(std::string startingScene) {
		_startingScene = startingScene;
	}
}