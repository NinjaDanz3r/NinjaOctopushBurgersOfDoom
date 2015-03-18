#ifndef EDITOR_H
#define EDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_editor.h"

class Project;

/// The editor.
/** @defgroup editor Editor
 * @{
 */

/// The main window of the editor.
class Editor : public QMainWindow {
	Q_OBJECT

	public:
		/// Create window.
		/**
		 * @param parent Parent widget.
		 */
		Editor(QWidget *parent = nullptr);

		/// Destructor.
		~Editor();

	public slots:
		/// Create new project.
		void newProject();

		/// Open project.
		void openProject();

		/// Save project.
		void saveProject();

		/// Close project.
		void closeProject();

		/// Import a model.
		void importModel();

		/// Import a texture.
		void importTexture();

		/// Handle selected item in tree widget being changed.
		void selectionChanged();

	private:
		void enableActions(bool enabled);
		QTreeWidgetItem* addTreeRoot(QString name);
		void deleteChildren(QTreeWidgetItem* item);

		Ui::EditorClass ui;
		Project* activeProject = nullptr;

		QTreeWidgetItem* modelsRoot;
		QTreeWidgetItem* texturesRoot;
};

/** @} */

#endif // EDITOR_H
