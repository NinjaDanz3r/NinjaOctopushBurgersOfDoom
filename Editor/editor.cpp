#include "editor.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QInputDialog>

Editor::Editor(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openProject()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveProject()));

	connect(ui.actionImportModel, SIGNAL(triggered()), this, SLOT(importModel()));

	modelsRoot = addTreeRoot("Models");
}

Editor::~Editor() {
	if (activeProject != nullptr)
		delete activeProject;

	delete modelsRoot;
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

	enableActions();
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

	enableActions();

	for (auto model : *activeProject->resources()->modelResources()) {
		QTreeWidgetItem *treeItem = new QTreeWidgetItem();
		treeItem->setText(0, QString::fromStdString(model->name));
		modelsRoot->addChild(treeItem);
	}
}

void Editor::saveProject() {
	activeProject->save();
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

	ModelResource* model = new ModelResource(name.toStdString(), filename.toStdString());
	activeProject->resources()->modelResources()->push_back(model);

	QTreeWidgetItem *treeItem = new QTreeWidgetItem();
	treeItem->setText(0, name);
	modelsRoot->addChild(treeItem);
}

void Editor::enableActions() {
	ui.actionSave->setEnabled(true);
	ui.actionImportModel->setEnabled(true);
}

QTreeWidgetItem* Editor::addTreeRoot(QString name) {
	QTreeWidgetItem* treeItem = new QTreeWidgetItem(ui.treeWidget);

	treeItem->setText(0, name);
	
	return treeItem;
}