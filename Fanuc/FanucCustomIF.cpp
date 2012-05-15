/*
 * FanucCustomIF.cpp
 *
 *  Created on: May 12, 2012
 *      Author: mziescha
 */
#include "FanucCustom.h"
using namespace std;

void FanucCustom::ifCondit(QString strIF, int lineCol)
{
    if (strIF.contains("AND"))
    {
        QStringList list = strIF.split(QRegExp("AND"));
        QString firstIF = list.takeFirst();
        QString secndIF = list.takeLast();
        int colFirstIF = lineCol;
        int colSecndIF = lineCol + firstIF.length() + 3;
        compare(firstIF, colFirstIF);
        compare(secndIF, colSecndIF);
    } else if (strIF.contains("OR"))
    {
        QStringList list = strIF.split(QRegExp("OR"));
        QString firstIF = list.takeFirst();
        QString secndIF = list.takeLast();
        int colFirstIF = lineCol;
        int colSecndIF = lineCol + firstIF.length() + 2;
        compare(firstIF, colFirstIF);
        compare(secndIF, colSecndIF);
    } else
        compare(strIF, lineCol);

}

bool FanucCustom::compare(QString strCompare, int startCompare)
{
    QStringList list;
    if (strCompare.startsWith("[") && strCompare.endsWith("]"))
    {
        strCompare.remove(0, 1);
        startCompare++;
        strCompare.remove(strCompare.length() - 1, 1);
    }

    if (strCompare.contains("NE"))
        list = strCompare.split(QRegExp("NE"));
    else if (strCompare.contains("EQ"))
        list = strCompare.split(QRegExp("EQ"));
    else if (strCompare.contains("GT"))
        list = strCompare.split(QRegExp("GT"));
    else if (strCompare.contains("LT"))
        list = strCompare.split(QRegExp("LT"));
    else if (strCompare.contains("LE"))
        list = strCompare.split(QRegExp("LE"));
    else if (strCompare.contains("GE"))
        list = strCompare.split(QRegExp("GE"));
    else
    {
        setFormat(startCompare, strCompare.length(), Qt::red);
        return false;
    }

    QString firstIF = list.takeFirst();
    QString secndIF = list.takeLast();
    int colFirstIF = startCompare;
    int colSecndIF = startCompare + firstIF.length() + 2;

    if (firstIF.contains(QRegExp("[\\+\\-\\*\\/]")))
    {
        if (!calculate(firstIF, colFirstIF)) setFormat(colFirstIF, firstIF.length(), Qt::red);
    } else
    {
        if (firstIF.contains(QRegExp("^\\[#\\d+$")))
        {
            firstIF.remove(0, 1);
            colFirstIF++;
        }
        if (firstIF.contains(QRegExp("^\\d+\\.*\\d*\\]$")))
        {
            firstIF.remove(firstIF.length() - 1, 1);

        }
        if (firstIF.contains(QRegExp("^\\[\\[#\\w+\\]$")))
        {
            firstIF.remove(0, 1);
            colFirstIF++;
        }
        if (firstIF.contains(QRegExp("^#\\[\\d+$")))
        {
            firstIF.remove(0, 2);
            colFirstIF = colFirstIF + 2;
        }
        if (chkKindOfVar(firstIF) == Digit) setFormat(colFirstIF, firstIF.length(), Qt::darkYellow);
        if (chkKindOfVar(firstIF) == Variable || chkKindOfVar(firstIF) == Symbolic) setFormat(colFirstIF, firstIF.length(), Qt::magenta);
        if (chkKindOfVar(firstIF) == PCodeVar) setFormat(colFirstIF, firstIF.length(), Qt::darkMagenta);
        if (chkKindOfVar(firstIF) == 0) setFormat(colFirstIF, firstIF.length(), Qt::red);
    }

    if (secndIF.contains(QRegExp("[\\+\\-\\*\\/]")))
    {
        if (!calculate(secndIF, colSecndIF)) setFormat(colSecndIF, secndIF.length(), Qt::red);
    } else
    {
        if (secndIF.contains(QRegExp("^\\[#\\d+$")))
        {
            secndIF.remove(0, 1);
            colSecndIF++;
        }
        if (secndIF.contains(QRegExp("^\\d+\\.*\\d*\\]$")))
        {
            secndIF.remove(secndIF.length() - 1, 1);

        }
        if (secndIF.contains(QRegExp("^\\[\\[#\\w+\\]$")))
        {
            secndIF.remove(0, 1);
            colSecndIF++;
        }
        if (secndIF.contains(QRegExp("^#\\[\\d+$")))
        {
            secndIF.remove(0, 2);
            colSecndIF = colSecndIF + 2;
        }

        if (chkKindOfVar(secndIF) == Digit) setFormat(colSecndIF, secndIF.length(), Qt::darkYellow);
        if (chkKindOfVar(secndIF) == Variable || chkKindOfVar(secndIF) == Symbolic) setFormat(colSecndIF, secndIF.length(), Qt::magenta);
        if (chkKindOfVar(secndIF) == PCodeVar) setFormat(colSecndIF, secndIF.length(), Qt::darkMagenta);
        if (chkKindOfVar(secndIF) == 0) setFormat(colSecndIF, secndIF.length(), Qt::red);
    }
    return true;
}

