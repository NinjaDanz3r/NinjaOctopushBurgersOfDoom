#ifndef EDITOR_H
#define EDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_editor.h"
#include "Project.h"

class Editor : public QMainWindow {
	Q_OBJECT

public:
	Editor(QWidget *parent = 0);
	~Editor();

public slots:
	void newProject();
	void openProject();
	void saveProject();
	void closeProject();

	void importModel();

private:
	void enableActions(bool enabled);
	QTreeWidgetItem* addTreeRoot(QString name);
	void deleteChildren(QTreeWidgetItem* item);

	Ui::EditorClass ui;
	Project* activeProject = nullptr;

	QTreeWidgetItem* modelsRoot;
};

#endif // EDITOR_H
