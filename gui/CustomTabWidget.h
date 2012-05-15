/*
 * CustomTabWidget.h
 *
 *  Created on: May 14, 2012
 *      Author: mziescha
 */

#ifndef CUSTOMTABWIDGET_H_
#define CUSTOMTABWIDGET_H_

#include <QtGui>
#include <QtGui/QTabWidget>

class CustomTabWidget: public QTabWidget
{
    Q_OBJECT

    public:
        CustomTabWidget();
        bool setNewText(int index, QString fileName);
        QTextEdit* getCurEditor()
        {
            QWidget *e = currentWidget();
            return dynamic_cast<QTextEdit*>(e);

        }

        QTextEdit* getEditor(int index)
        {
            QWidget *e = widget(index);
            return dynamic_cast<QTextEdit*>(e);

        }
};

#endif /* CUSTOMTABWIDGET_H_ */
