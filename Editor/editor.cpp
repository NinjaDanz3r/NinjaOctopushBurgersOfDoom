#include "editor.h"
#include <OBJModel.h>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QInputDialog>

Editor::Editor(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openProject()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveProject()));
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(closeProject()));

	connect(ui.actionImportModel, SIGNAL(triggered()), this, SLOT(importModel()));

	modelsRoot = addTreeRoot("Models");
}

Editor::~Editor() {
	if (activeProject != nullptr)
		delete activeProject;

	deleteChildren(modelsRoot);
	delete modelsRoot;
}

void Editor::newProject() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Project"), "", tr("Project (*.proj);;All Files (*)"));
	if (filename.isEmpty()) {
		return;
	}

	closeProject();

	activeProject = new Project();
	activeProject->setFilename(filename.toStdString());

	enableActions(true);
}

void Editor::openProject() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Project"), "", tr("Project (*.proj);;All Files (*)"));
	if (filename.isEmpty()) {
		return;
	}

	closeProject();

	activeProject = new Project();
	activeProject->setFilename(filename.toStdString());
	activeProject->load();

	enableActions(true);

	for (auto model : *activeProject->resources()->modelResources()) {
		QTreeWidgetItem *treeItem = new QTreeWidgetItem();
		treeItem->setText(0, QString::fromStdString(model->name));
		modelsRoot->addChild(treeItem);
	}
}

void Editor::saveProject() {
	activeProject->save();
}

void Editor::closeProject() {
	if (activeProject != nullptr) {
		delete activeProject;
		activeProject = nullptr;
	}

	deleteChildren(modelsRoot);

	enableActions(false);
}

void Editor::importModel() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Import Model"), "", tr("OBJ Model (*.obj);;All Files (*)"));
	if (filename.isEmpty()) {
		return;
	}

	QString name = QInputDialog::getText(this, tr("Enter Model Name"), tr("Model name:"));
	if (name.isEmpty()) {
		return;
	}

	ModelResource* model = new ModelResource(name.toStdString(), new OBJModel(filename.toStdString().c_str()));
	activeProject->resources()->modelResources()->push_back(model);

	QTreeWidgetItem *treeItem = new QTreeWidgetItem();
	treeItem->setText(0, name);
	modelsRoot->addChild(treeItem);
}

void Editor::enableActions(bool enabled) {
	ui.actionSave->setEnabled(enabled);
	ui.actionImportModel->setEnabled(enabled);
	ui.actionClose->setEnabled(enabled);
}

QTreeWidgetItem* Editor::addTreeRoot(QString name) {
	QTreeWidgetItem* treeItem = new QTreeWidgetItem(ui.treeWidget);
	treeItem->setText(0, name);
	return treeItem;
}

void Editor::deleteChildren(QTreeWidgetItem* item) {
	QList<QTreeWidgetItem*> children = item->takeChildren();
	for (auto child : children) {
		delete child;
	}
}