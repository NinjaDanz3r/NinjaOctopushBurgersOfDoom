#include <GL/glew.h>
#include "editor.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	Editor w;
	w.show();
	glewInit();
	return a.exec();
}
