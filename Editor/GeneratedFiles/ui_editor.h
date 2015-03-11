/********************************************************************************
** Form generated from reading UI file 'editor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "previewwidget.h"

QT_BEGIN_NAMESPACE

class Ui_EditorClass
{
public:
    QAction *actionQuit;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionImportModel;
    QAction *actionClose;
    QAction *actionImportTexture;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    PreviewWidget *previewWidget;
    QTreeWidget *treeWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuImport;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EditorClass)
    {
        if (EditorClass->objectName().isEmpty())
            EditorClass->setObjectName(QStringLiteral("EditorClass"));
        EditorClass->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EditorClass->sizePolicy().hasHeightForWidth());
        EditorClass->setSizePolicy(sizePolicy);
        actionQuit = new QAction(EditorClass);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionQuit->setMenuRole(QAction::QuitRole);
        actionNew = new QAction(EditorClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Editor/Resources/document-new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(EditorClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Editor/Resources/document-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(EditorClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Editor/Resources/media-floppy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionSave_As = new QAction(EditorClass);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionImportModel = new QAction(EditorClass);
        actionImportModel->setObjectName(QStringLiteral("actionImportModel"));
        actionImportModel->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Editor/Resources/media-model.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImportModel->setIcon(icon3);
        actionClose = new QAction(EditorClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionClose->setEnabled(false);
        actionImportTexture = new QAction(EditorClass);
        actionImportTexture->setObjectName(QStringLiteral("actionImportTexture"));
        actionImportTexture->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Editor/Resources/media-texture.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImportTexture->setIcon(icon4);
        centralWidget = new QWidget(EditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        previewWidget = new PreviewWidget(centralWidget);
        previewWidget->setObjectName(QStringLiteral("previewWidget"));

        horizontalLayout->addWidget(previewWidget);

        treeWidget = new QTreeWidget(centralWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);
        treeWidget->setColumnCount(1);
        treeWidget->header()->setVisible(false);

        horizontalLayout->addWidget(treeWidget);

        EditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuImport = new QMenu(menuBar);
        menuImport->setObjectName(QStringLiteral("menuImport"));
        EditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EditorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuImport->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuImport->addAction(actionImportTexture);
        menuImport->addSeparator();
        menuImport->addAction(actionImportModel);

        retranslateUi(EditorClass);
        QObject::connect(actionQuit, SIGNAL(triggered()), EditorClass, SLOT(close()));

        QMetaObject::connectSlotsByName(EditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditorClass)
    {
        EditorClass->setWindowTitle(QApplication::translate("EditorClass", "Editor", 0));
        actionQuit->setText(QApplication::translate("EditorClass", "Quit", 0));
        actionNew->setText(QApplication::translate("EditorClass", "New...", 0));
        actionNew->setShortcut(QApplication::translate("EditorClass", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("EditorClass", "Open...", 0));
        actionOpen->setShortcut(QApplication::translate("EditorClass", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("EditorClass", "Save", 0));
        actionSave->setShortcut(QApplication::translate("EditorClass", "Ctrl+S", 0));
        actionSave_As->setText(QApplication::translate("EditorClass", "Save As...", 0));
        actionImportModel->setText(QApplication::translate("EditorClass", "Model", 0));
        actionClose->setText(QApplication::translate("EditorClass", "Close", 0));
        actionImportTexture->setText(QApplication::translate("EditorClass", "Texture", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("EditorClass", "1", 0));
        menuFile->setTitle(QApplication::translate("EditorClass", "File", 0));
        menuImport->setTitle(QApplication::translate("EditorClass", "Import", 0));
    } // retranslateUi

};

namespace Ui {
    class EditorClass: public Ui_EditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
