/*
 * MainWindowSlots.cpp
 *
 *  Created on: May 4, 2012
 *      Author: mziescha
 */
#include <iostream>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QTextStream>
#include "MainWindow.h"

using namespace Qt;

void MainWindow::newProject()
{
    statusBar()->showMessage(tr("TODO => void MainWindow::newProject()"), STATUSTIME);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Document"), QDir::currentPath(), tr("Document files (*.doc *.rtf);;All files (*.*)"));
    if (fileName.isEmpty() || fileName == "") return;
    QFile file(fileName);
    if (!file.open((QIODevice::ReadOnly | QIODevice::Text)))
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    QTextStream in(&file);
    QTextEdit* edit = new QTextEdit();
    edit->setLineWrapMode(QTextEdit::NoWrap);
    edit->setFont(QFont("Courier"));
    highlighter = new FanucCustom(edit->document());
    edit->setText(in.readAll());
    file.close();

    content->addTab(edit, "new");
    content->setNewText(content->count() - 1, fileName);
    content->setCurrentIndex(content->count() - 1);
    content->currentWidget()->setObjectName(fileName);

    statusBar()->showMessage(tr("Loaded '%1'").arg(fileName), STATUSTIME);
}
void MainWindow::newTab()
{
    QTextEdit* edit = new QTextEdit();
    edit->setLineWrapMode(QTextEdit::NoWrap);
    edit->setFont(QFont("Courier"));
    highlighter = new FanucCustom(edit->document());
    content->addTab(edit, "new");
    content->setCurrentIndex(content->count() - 1);
}

void MainWindow::save()
{
    QString fileName = content->currentWidget()->objectName();
    if (fileName.isEmpty()) fileName = QFileDialog::getSaveFileName(this, tr("Choose a file name"), ".", tr("FANUC (*.*)"));
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Dock Widgets"), tr("Cannot write file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return;
    }
    content->setNewText(content->currentIndex(), fileName);
    content->currentWidget()->setObjectName(fileName);
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << content->getCurEditor()->toPlainText();
    QApplication::restoreOverrideCursor();
    statusBar()->showMessage(tr("Saved '%1'").arg(fileName), STATUSTIME);
}
void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Choose a file name"), ".", tr("FANUC (*.*)"));
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Dock Widgets"), tr("Cannot write file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return;
    }
    content->setNewText(content->currentIndex(), fileName);
    content->currentWidget()->setObjectName(fileName);
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << content->getCurEditor()->toPlainText();
    QApplication::restoreOverrideCursor();
    statusBar()->showMessage(tr("Saved '%1'").arg(fileName), STATUSTIME);
}
void MainWindow::print()
{
#ifndef QT_NO_PRINTDIALOG
    QTextDocument *document = content->getCurEditor()->document();
    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (dlg->exec() != QDialog::Accepted) return;
    document->print(&printer);
    statusBar()->showMessage(tr("Ready"), STATUSTIME);
#endif
}
void MainWindow::closeTab()
{
    if (content->currentIndex() > 0) content->removeTab(content->currentIndex());
}
void MainWindow::quit()
{
    close();
}
void MainWindow::jumpToLine()
{
    statusBar()->showMessage(tr("TODO => void MainWindow::jumpToLine(QTabWidget *content)"), STATUSTIME);
}

void MainWindow::createActions()
{
    newProjAct = new QAction(QIcon(":/images/newproj.png"), tr("&New project"), this);
    newProjAct->setStatusTip(tr("New project"));
    connect(newProjAct, SIGNAL(triggered()), this, SLOT(newProject()));
    nFilAct = new QAction(QIcon(":/images/new.png"), tr("N&ew Tab"), this);
    nFilAct->setShortcuts(QKeySequence::New);
    nFilAct->setStatusTip(tr("Open a new Tab"));
    connect(nFilAct, SIGNAL(triggered()), this, SLOT(newTab()));
    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current file"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
    saveAsAct = new QAction(QIcon(":/images/save.png"), tr("S&ave as ..."), this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save file to name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
    printAct = new QAction(QIcon(":/images/print.png"), tr("&Print"), this);
    printAct->setShortcut(QKeySequence::Print);
    printAct->setStatusTip(tr("Save the current file"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
    closeAct = new QAction(QIcon(":/images/closetab.png"), tr("&close Tab"), this);
    closeAct->setShortcut(QKeySequence::Close);
    closeAct->setStatusTip(tr("Close the current document"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(closeTab()));
    quitAct = new QAction(QIcon(":/images/quit.png"), tr("&Quit"), this);
    quitAct->setShortcut(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit application"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));
    undoAct = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    undoAct->setShortcut(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo previous action"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));
    redoAct = new QAction(QIcon(":/images/redo.png"), tr("&Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last action"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(redo()));
    oFilAct = new QAction(QIcon(":/images/redo.png"), tr("&Open file"), this);
    oFilAct->setShortcut(QKeySequence::Open);
    oFilAct->setStatusTip(tr("Open existing file"));
    connect(oFilAct, SIGNAL(triggered()), this, SLOT(openFile()));
}

void MainWindow::undo()
{
}
void MainWindow::redo()
{
}
