/*
 * OutlineDock.h
 *
 *  Created on: May 15, 2012
 *      Author: mziescha
 */

#ifndef OUTLINEDOCK_H_
#define OUTLINEDOCK_H_

#include <QtGui>

#include <QtGui/QDockWidget>
#include "CustomTabWidget.h"
class OutlineDock: public QDockWidget
{
    Q_OBJECT
    public:
        OutlineDock(QWidget* parent);

    private slots:
        void updateOutline();
};

#endif /* OUTLINEDOCK_H_ */
