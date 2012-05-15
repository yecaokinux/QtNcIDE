/*
 * MainWindow.h
 *
 *  Created on: May 2, 2012
 *      Author: mziescha
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui>
#include <QtGui/QMainWindow>
#include <QtGui/QDockWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QTextEdit>
#include <QtGui/QStatusBar>
#include <QtGui/QPrintDialog>

#include "../common/FanucCustom.h"
#include "CustomTabWidget.h"
#include "OutlineDock.h"

#define STATUSTIME 7000

class QAction;
class QListWidget;
class QListWidgetItem;
class QMenu;
class QTextEdit;
class QStatusBar;

class MainWindow: public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow()
        {
            setMinimumSize(700, 400);
            createContent();
            createActions();
            createOutline();
            createProject();
            createMenuBar();
            createToolBar();
            statusBar()->showMessage("Ready");
        }

        virtual ~MainWindow();

    private:
        void createOutline();
        void createContent();
        void createMenuBar();
        void createEditMenu();
        void createFileMenu();
        void createToolBar();
        void createJumper();
        void createProject();
        void createActions();

        QAction *nFilAct;
        QAction *newProjAct;
        QAction *saveAct;
        QAction *saveAsAct;
        QAction *printAct;
        QAction *quitAct;
        QAction *closeAct;
        QAction *undoAct;
        QAction *redoAct;
        QAction *oFilAct;

        QMenu *fileMenu;
        QMenu *editMenu;
        QMenu *helpMenu;
        QMenu *viewMenu;
        OutlineDock *outline;
        QDockWidget *project;
        CustomTabWidget *content;
        QListWidget *outlineList;

        QToolBar *fileToolBar;
        QToolBar *editToolBar;
        QToolBar *viewToolBar;

        FanucCustom* highlighter;

    public slots:
        void closeTab();

    private slots:
        void newTab();
        void newProject();
        void openFile();
        void save();
        void saveAs();
        void print();
        void quit();
        void undo();
        void redo();
        void jumpToLine();

};

#endif /* MAINWINDOW_H_ */
