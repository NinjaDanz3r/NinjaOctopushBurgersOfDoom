#include "editor.h"
#include <OBJModel.h>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QInputDialog>
#include "convert.h"

Editor::Editor(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openProject()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveProject()));
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(closeProject()));

	connect(ui.actionImportModel, SIGNAL(triggered()), this, SLOT(importModel()));
	connect(ui.actionImportTexture, SIGNAL(triggered()), this, SLOT(importTexture()));

	connect(ui.treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

	texturesRoot = addTreeRoot("Textures");
	modelsRoot = addTreeRoot("Models");
}

Editor::~Editor() {
	if (activeProject != nullptr)
		delete activeProject;

	deleteChildren(modelsRoot);
	delete modelsRoot;

	deleteChildren(texturesRoot);
	delete texturesRoot;
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

	for (auto texture : *activeProject->resources()->textureResources()) {
		QTreeWidgetItem *treeItem = new QTreeWidgetItem();
		treeItem->setText(0, QString::fromStdString(texture.first));
		texturesRoot->addChild(treeItem);
	}

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
	deleteChildren(texturesRoot);

	enableActions(false);

	ui.previewWidget->setPreviewTexture(nullptr);
	ui.previewWidget->repaint();
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

void Editor::importTexture() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Import Texture"), "", tr("Image Files (*.png *.jpg *.jpeg *.tga *.bmp);;All Files (*)"));
	if (filename.isEmpty()) {
		return;
	}

	QString name = QInputDialog::getText(this, tr("Enter Texture Name"), tr("Texture name:"));
	if (name.isEmpty()) {
		return;
	}

	convert::convertImage(filename.toStdString().c_str(), (activeProject->directory() + "/Textures/" + name.toStdString() + ".tga").c_str());

	TextureResource* texture = new TextureResource(name.toStdString(), activeProject->directory());
	(*activeProject->resources()->textureResources())[texture->name] = texture;

	QTreeWidgetItem *treeItem = new QTreeWidgetItem();
	treeItem->setText(0, name);
	texturesRoot->addChild(treeItem);
}

void Editor::selectionChanged() {
	if (ui.treeWidget->selectedItems().length() > 0) {
		QTreeWidgetItem* selected = ui.treeWidget->selectedItems()[0];

		if (selected->parent() == texturesRoot) {
			ui.previewWidget->setPreviewTexture((*activeProject->resources()->textureResources())[selected->text(0).toStdString()]->texture());
			ui.previewWidget->repaint();
		}
	}
}

void Editor::enableActions(bool enabled) {
	ui.actionSave->setEnabled(enabled);
	ui.actionClose->setEnabled(enabled);
	ui.actionImportModel->setEnabled(enabled);
	ui.actionImportTexture->setEnabled(enabled);
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