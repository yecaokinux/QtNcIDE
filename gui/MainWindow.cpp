/*
 * MainWindow.cpp
 *
 *  Created on: May 2, 2012
 *      Author: mziescha
 */

#include "MainWindow.h"
using namespace std;

/***
 *
 */
void MainWindow::createMenuBar()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newProjAct);
    fileMenu->addAction(nFilAct);
    fileMenu->addAction(oFilAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);
    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(outline->toggleViewAction());
    viewMenu->addAction(project->toggleViewAction());
}

void MainWindow::createToolBar()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(nFilAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(printAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(undoAct);

    viewToolBar = addToolBar(tr("View"));
    viewToolBar->addAction(outline->toggleViewAction());
    viewToolBar->addAction(project->toggleViewAction());
}

void MainWindow::createOutline()
{
    outline = new OutlineDock(content);
    outlineList = new QListWidget(content);
    outline->setWidget(outlineList);
    outline->setMinimumWidth(200);
    addDockWidget(Qt::RightDockWidgetArea, outline);
    connect(outlineList, SIGNAL(itemDoubleClicked()), this, SLOT(jumpToLine()));
}


void MainWindow::createContent()
{
    content = new CustomTabWidget;
    QTextEdit* edit = new QTextEdit();
    edit->setFont(QFont("Courier"));
    highlighter = new FanucCustom(edit->document());
    content->addTab(edit, "Start");
    setCentralWidget(content);
}

void MainWindow::createProject()
{
    project = new QDockWidget(tr("&Project"));
    project->setMinimumWidth(200);
    addDockWidget(Qt::LeftDockWidgetArea, project);
}

MainWindow::~MainWindow()
{
    // TODO Auto-generated destructor stub
}

