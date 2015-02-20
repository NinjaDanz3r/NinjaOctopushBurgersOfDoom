#include "editor.h"
#include <QtWidgets/QFileDialog>

Editor::Editor(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openProject()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveProject()));
}

Editor::~Editor() {
	if (activeProject != nullptr)
		delete activeProject;
}

void Editor::newProject() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Project"), "", tr("Project (*.proj);;All Files (*)"));
	if (filename.isEmpty()) {
		return;
	}

	if (activeProject != nullptr)
		delete activeProject;

	activeProject = new Project();
	activeProject->filename = filename.toStdString();

	ui.actionSave->setEnabled(true);
}

void Editor::openProject() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Project"), "", tr("Project (*.proj);;All Files (*)"));
	if (filename.isEmpty()) {
		return;
	}

	if (activeProject != nullptr)
		delete activeProject;

	activeProject = new Project();
	activeProject->filename = filename.toStdString();
	activeProject->load();

	ui.actionSave->setEnabled(true);
}

void Editor::saveProject() {
	activeProject->save();
}
