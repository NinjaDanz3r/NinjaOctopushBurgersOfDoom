#ifndef EDITOR_H
#define EDITOR_H

#include <Project.h>
#include <QtWidgets/QMainWindow>
#include "ui_editor.h"

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
		void importTexture();

	private:
		void enableActions(bool enabled);
		QTreeWidgetItem* addTreeRoot(QString name);
		void deleteChildren(QTreeWidgetItem* item);

		Ui::EditorClass ui;
		Project* activeProject = nullptr;

		QTreeWidgetItem* modelsRoot;
		QTreeWidgetItem* texturesRoot;
};

#endif // EDITOR_H
