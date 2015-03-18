#include "settings.h"
#include <SimpleIni.h>
#include <string>

namespace settings {
	bool _logging;

	void load(const char* filename) {
		CSimpleIniA ini;
		ini.SetUnicode();
		ini.LoadFile(filename);

		_logging = ini.GetBoolValue("Debug", "Logging");
	}

	void save(const char* filename) {
		CSimpleIniA ini;
		ini.SetUnicode();

		ini.SetBoolValue("Debug", "Logging", _logging);

		SI_Error rc = ini.SaveFile(filename);
		if (rc < 0)
			fputs("Couldn't save settings", stderr);
	}

	bool logging() {
		return _logging;
	}

	void setLogging(bool logging) {
		_logging = logging;
	}
}