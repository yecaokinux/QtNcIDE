/*
 * CustomTabWidget.cpp
 *
 *  Created on: May 14, 2012
 *      Author: mziescha
 */

#include "CustomTabWidget.h"

CustomTabWidget::CustomTabWidget()
{
    setTabsClosable(true);
    setMovable(true);
}

bool CustomTabWidget::setNewText(int index, QString fileName)
{
    QString title;
    if (fileName.contains(QRegExp("\\/")))
    {
        QStringList l = fileName.split(QRegExp("\\/"));
        title = l.takeLast();
    } else if (fileName.contains(QRegExp("\\")))
    {
        QStringList l = fileName.split(QRegExp("\\"));
        title = l.takeLast();

    } else
    {
        title = fileName;
    }
    setTabText(index, title);
    return true;
}



