/*
 * FanucCustom.cpp
 *
 *  Created on: May 4, 2012
 *      Author: mziescha
 */

#include "FanucCustom.h"
#include <QtGui/QListWidgetItem>
using namespace std;

void FanucCustom::highlightBlock(const QString &text)
{
    int state = previousBlockState();
    int start = 0;
    numberLength = 0;
    int sqbracketOpen = 0;

    for (int i = 0; i < text.length(); ++i)
    {
        if (text.mid(i, 1) == "[") sqbracketOpen++;
        if (text.mid(i, 1) == "]") sqbracketOpen--;

    }
    if (sqbracketOpen != 0)
    {
        setFormat(0, text.length(), Qt::red);
        return;
    }
    /***
     * at first seperate comments from text
     */
    QString noComment;
    if (text.contains("("))
    {
        QStringList strl = text.split("(");
        if (strl.size() > 2)
            setFormat(0, text.length(), Qt::red);
        else
        {
            noComment = strl.takeFirst();
            QString l = strl.takeLast();
            setFormat(noComment.length(), l.length() + 1, Qt::lightGray);
        }
    } else
        noComment = text;

    /**
     * seperate line number and collect then for Outline
     */
    if (noComment.contains(QRegExp("^N\\d+")))
    {
        QRegExp rx;
        QString number;
        rx.setPattern("^N\\d+");
        if (rx.indexIn(noComment) != -1)
        {
            number = rx.cap(0);
            numberLength = number.length();
            noComment.remove(0, numberLength);

//            new QListWidgetItem(number, outline); //geht nicht:(

            setFormat(0, numberLength, Qt::darkGray);
        }
    }

    /**
     * search noComment text
     */
    for (int i = 0; i < noComment.length(); ++i)
    {
        if (noComment.mid(i, 4) == "M98<" && state == NormalState)
        {
            start = i;
            state = SubroutineCall;
        } else if (noComment.mid(i, 3) == "IF[")
        {
            start = i;
            state = IFCondition;
        } else if (noComment.mid(i, 4).contains(QRegExp("^[G]\\d+")) && state == NormalState)
        {
            start = i;
            state = GComment;
        } else if (noComment.mid(i, noComment.length() - i).contains(QRegExp("^[M](?:#\\d+)*(?:\\d+)*(?:\\[#\\w+\\])*(?:[V]\\d+)*(?:[H]\\d+)*"))
                && state == NormalState)
        {
            start = i;
            state = MComment;
        } else if (noComment.mid(i, noComment.length() - i).contains(QRegExp("^[AUZXCY](?:\\d+=)*(?:\\d+)*(?:\\[#\\w+\\])*")) && state == NormalState)
        {
            start = i;
            state = Axis;
        } else if (noComment.mid(i, noComment.length() - i).contains(QRegExp("^[F](?:\\d+)*(?:\\[#\\w+\\])*")) && state == NormalState)
        {

            start = i;
            state = Feed;
        } else if (noComment.mid(i, noComment.length() - i).contains("=") && state == NormalState)
        {
            start = i;
            state = Calc;
        }
//        cout << "Feed: " << noComment.mid(i, noComment.length() - i).toStdString() << endl;
//        cout << "state: " << state << endl;
        switch (state)
        {
            case MComment:
            {
                QRegExp rx;
                int col = start + numberLength;
                rx.setPattern("[M](?:#\\d+)*(?:\\d+)*(?:\\[#\\w+\\])*(?:[V]\\d+)*(?:[H]\\d+)*");
                if (rx.indexIn(noComment.mid(start, noComment.length() - start)) != -1)
                {
                    QString feed = rx.cap(0);
                    setFormat(col, feed.length(), Qt::darkCyan);
                    feed.remove(0, 1);
                    col++;

                    if (feed.contains(QRegExp("[VH]")))
                    {
                        QStringList list = feed.split(QRegExp("[VH]"));
                        QString f = list.takeFirst();
                        QString l = list.takeLast();
                        if (chkKindOfVar(f) == Symbolic) setFormat(col, f.length(), Qt::magenta);
                        if (chkKindOfVar(f) == PCodeVar) setFormat(col, f.length(), Qt::darkMagenta);
                        if (chkKindOfVar(f) == Variable) setFormat(col, f.length(), Qt::magenta);
                        if (chkKindOfVar(f) == 0) setFormat(col, l.length(), Qt::red);
                        col = col + f.length() + 1;
                        if (chkKindOfVar(l) == Symbolic) setFormat(col, l.length(), Qt::magenta);
                        if (chkKindOfVar(l) == PCodeVar) setFormat(col, l.length(), Qt::darkMagenta);
                        if (chkKindOfVar(l) == Variable) setFormat(col, l.length(), Qt::magenta);
                        if (chkKindOfVar(l) == 0) setFormat(col, l.length(), Qt::red);
                    } else
                    {
                        if (chkKindOfVar(feed) == Digit) setFormat(col, feed.length(), Qt::darkCyan);
                        if (chkKindOfVar(feed) == Symbolic) setFormat(col, feed.length(), Qt::magenta);
                        if (chkKindOfVar(feed) == PCodeVar) setFormat(col, feed.length(), Qt::darkMagenta);
                        if (chkKindOfVar(feed) == Variable) setFormat(col, feed.length(), Qt::magenta);
                        if (chkKindOfVar(feed) == 0) setFormat(col, feed.length(), Qt::red);
                    }
                    i = start + feed.length();
                }
            }
                state = NormalState;
                break;
            case Feed:
            {
                QRegExp rx;
                int col = start + numberLength;
                rx.setPattern("[F](?:\\d+)*(?:\\[#\\w+\\])*");
                if (rx.indexIn(noComment.mid(start, noComment.length() - start)) != -1)
                {
                    QString feed = rx.cap(0);
                    setFormat(col, feed.length(), Qt::darkCyan);
                    feed.remove(0, 1);
                    col++;
                    if (chkKindOfVar(feed) == Digit) setFormat(col, feed.length(), Qt::darkYellow);
                    if (chkKindOfVar(feed) == Symbolic) setFormat(col, feed.length(), Qt::magenta);
                    if (chkKindOfVar(feed) == PCodeVar) setFormat(col, feed.length(), Qt::darkMagenta);
                    if (chkKindOfVar(feed) == Variable) setFormat(col, feed.length(), Qt::magenta);
                    if (chkKindOfVar(feed) == 0) setFormat(col, feed.length(), Qt::red);
                    i = start + feed.length();
                }
            }
                state = NormalState;
                break;
            case Axis:
            {
                QRegExp rx;
                int col = start + numberLength;
                rx.setPattern("[AUZXCY](?:\\d+=)*(?:\\d+)*(?:\\[#\\w+\\])*");
                if (rx.indexIn(noComment.mid(start, noComment.length() - start)) != -1)
                {
                    QString axis = rx.cap(0);
                    if (axis.contains("="))
                    {
                        QStringList list = axis.split(QRegExp("="));
                        QString f = list.takeFirst();
                        QString l = list.takeLast();
                        setFormat(col, f.length(), Qt::darkCyan);
                        col = col + f.length() + 1;
                        if (chkKindOfVar(l) == Digit) setFormat(col, l.length(), Qt::darkYellow);
                        if (chkKindOfVar(l) == Symbolic) setFormat(col, l.length(), Qt::magenta);
                        if (chkKindOfVar(l) == PCodeVar) setFormat(col, l.length(), Qt::darkMagenta);
                        if (chkKindOfVar(l) == Variable) setFormat(col, l.length(), Qt::magenta);
                        if (chkKindOfVar(l) == 0) setFormat(col, l.length(), Qt::red);
                    } else
                    {
                        setFormat(col, axis.length(), Qt::darkCyan);
                        col = col + axis.length();
                    }
                    i = start + axis.length() - 1;
                }

            }
                state = NormalState;
                break;
            case GComment:
            {
                QRegExp rx;
                rx.setPattern("[G]\\d+");
                if (rx.indexIn(noComment.mid(start, 4)) != -1)
                {
                    QString gCode = rx.cap(0);
                    setFormat(start + numberLength, gCode.length(), Qt::cyan);
                    i = start + gCode.length() - 1;
                }

            }
                state = NormalState;
                break;
            case Calc:
            {
                QString cnoComment = noComment.mid(start, noComment.length() - start);
                QStringList tmp = cnoComment.split("=");
                QString f = tmp.takeFirst();
                QString l = tmp.takeLast();

                if (chkKindOfVar(f) == Digit) setFormat(start + numberLength, f.length(), Qt::darkYellow);
                if (chkKindOfVar(f) == Variable || chkKindOfVar(f) == Symbolic) setFormat(start + numberLength, f.length(), Qt::magenta);
                if (chkKindOfVar(f) == PCodeVar) setFormat(start + numberLength, f.length(), Qt::darkMagenta);
                if (chkKindOfVar(f) == 0) setFormat(start + numberLength, f.length(), Qt::red);

                start = start + f.length() + 1;

                if (l.contains(QRegExp("[\\+\\-\\*\\/]")))
                {
                    if (!calculate(l, start + numberLength)) setFormat(start + numberLength, l.length(), Qt::red);
                } else
                {
                    if (chkKindOfVar(l) == Digit) setFormat(start + numberLength, l.length(), Qt::darkYellow);
                    if (chkKindOfVar(l) == Variable || chkKindOfVar(l) == Symbolic) setFormat(start + numberLength, l.length(), Qt::magenta);
                    if (chkKindOfVar(l) == PCodeVar) setFormat(start + numberLength, l.length(), Qt::darkMagenta);
                    if (chkKindOfVar(l) == 0) setFormat(start + numberLength, l.length(), Qt::red);
                }
                i = start + l.length();

            }
                state = NormalState;
                break;
            case SubroutineCall:
                if (noComment.mid(i, 1) == ">")
                {
                    state = NormalState;
                    setFormat(start + numberLength, i - start + 1, Qt::green);
                } else
                    setFormat(start + numberLength, i - start + 1, Qt::red);
                break;
            case IFCondition:
            {
                if (noComment.mid(i, 5) == "]GOTO" || noComment.mid(i, 5) == "]THEN")
                {
                    setFormat(start + numberLength, i - start + 5, Qt::blue);
                    int startIF = start + 3;
                    int ifLenght = i - startIF;
                    QString ifnoComment = noComment.mid(startIF, ifLenght);
                    ifCondit(ifnoComment, startIF + numberLength);
                    i = i + 4;
                    state = NormalState;
                } else
                    setFormat(start + numberLength, i - start + 1, Qt::red);
            }
                break;
            default:
                state = NormalState;
                break;
        }
    }
    numberLength = 0;
}

bool FanucCustom::calculate(QString str, int startStr)
{
    QStringList list = str.split(QRegExp("[\\+\\-\\*\\/]"));
    for (int j = 0; j < list.length(); ++j)
    {
        int end = 1;
        QString m = list.at(j);

        if (m.contains(QRegExp("^\\[#\\d+$")))
        {
            m.remove(0, 1);
            startStr++;
        }
        if (m.contains(QRegExp("^\\d+\\.*\\d*\\]$")))
        {
            m.remove(m.length() - 1, 1);
            end++;
        }
        if (m.contains(QRegExp("^\\[\\[#\\w+\\]$")))
        {
            m.remove(0, 1);
            startStr++;
        }
        if (m.contains(QRegExp("^#\\[\\d+$")))
        {
            m.remove(0, 2);
            startStr = startStr + 2;
        }
        if (m.contains(QRegExp("^\\d+\\]\\]$")))
        {
            m.remove(m.length() - 2, 2);
            end = end + 2;
        }

        if (chkKindOfVar(m) == Digit) setFormat(startStr, m.length(), Qt::darkYellow);
        if (chkKindOfVar(m) == Variable || chkKindOfVar(m) == Symbolic) setFormat(startStr, m.length(), Qt::magenta);
        if (chkKindOfVar(m) == PCodeVar) setFormat(startStr, m.length(), Qt::darkMagenta);
        if (chkKindOfVar(m) == 0) setFormat(startStr, m.length(), Qt::red);
        startStr = startStr + m.length() + end;

    }
    return true;
}

int FanucCustom::chkKindOfVar(QString strVar)
{
    QRegExp var("#\\d+");
    QRegExp sym("\\[#\\w+\\]");
    int bracket = 0;
    for (int j = 0; j < strVar.length(); ++j)
    {
        if (strVar.mid(j, 1) == "[") bracket++;
        if (strVar.mid(j, 1) == "[") bracket--;
    }
    if (bracket != 0) return 0;
    if (var.exactMatch(strVar))
    {
        strVar.remove(0, 1);
        if (strVar.toInt() >= 100000)
            return 0;
        else if (strVar.toInt() >= 10000)
            return PCodeVar;
        else
            return Variable;
    } else if (sym.exactMatch(strVar))
        return Symbolic;
    else if (strVar.toDouble() || strVar.toInt() || strVar == "0") return Digit;
    return 0;
}
