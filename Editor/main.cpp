#include <GL/glew.h>
#include "editor.h"
#include <util.h>
#include "settings.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	settings::load(util::savePath("editor_settings.ini").c_str());
	if (settings::logging())
		freopen(util::savePath("editor_log.txt").c_str(), "a", stderr);
	util::logWithTime("Editor started");

	QApplication a(argc, argv);
	Editor w;
	w.show();
	int result = a.exec();

	util::logWithTime("Editor ended");
	settings::save(util::savePath("editor_settings.ini").c_str());

	return result;
}
