//============================================================================
// Name        : QtNcIde.cpp
// Author      : Mario Zieschang
// Version     :
// Copyright   : GPL2
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include <QtGui/QApplication>

#include "gui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(dockwidgets);
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
