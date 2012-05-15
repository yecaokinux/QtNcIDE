/*
 * OutlineDock.cpp
 *
 *  Created on: May 15, 2012
 *      Author: mziescha
 */
#include <iostream>

#include "OutlineDock.h"

using namespace std;

OutlineDock::OutlineDock(QWidget *parent)
{
    setWindowTitle("Outline");
    setParent(parent);

    //CustomTabWidget *p = dynamic_cast<CustomTabWidget*>(parent);


//    connect(p->getCurEditor(), SIGNAL(textChanged()), this, SLOT(textChanged()));
}

void OutlineDock::updateOutline()
{
    cout << "TODO => void OutlineDock::updateOutline()" << endl;
}
