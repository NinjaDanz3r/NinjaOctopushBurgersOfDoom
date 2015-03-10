#include <GL/glew.h>
#include "editor.h"
#include <util.h>

#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	freopen(util::savePath("editor_log.txt").c_str(), "a", stderr);
	QApplication a(argc, argv);
	Editor w;
	w.show();
	return a.exec();
}
