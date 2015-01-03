#include "settings.h"
#include <SimpleIni.h>

namespace settings {
	float _mouseSensitivity;
	bool _freeConsole;

	void load(const char* filename) {
		CSimpleIniA ini;
		ini.SetUnicode();
		ini.LoadFile(filename);

		_mouseSensitivity = static_cast<float>(ini.GetDoubleValue("controls", "mouseSensitivity", 0.5f));
		_freeConsole = ini.GetBoolValue("debug", "freeConsole", true);
	}

	void save(const char* filename) {
		CSimpleIniA ini;
		ini.SetUnicode();

		ini.SetDoubleValue("controls", "mouseSensitivity", _mouseSensitivity);
		ini.SetBoolValue("debug", "freeConsole", _freeConsole);

		SI_Error rc = ini.SaveFile(filename);
		if (rc < 0)
			fputs("Couldn't save settings", stderr);
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

	bool freeConsole() {
		return _freeConsole;
	}

	void setFreeConsole(bool free) {
		_freeConsole = free;
	}
}