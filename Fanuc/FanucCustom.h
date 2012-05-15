/*
 * FanucCustom.h
 *
 *  Created on: May 4, 2012
 *      Author: mziescha
 */

#ifndef EDITOR_H_
#define EDITOR_H_

#include <map>
#include <string>
#include <QtGui/QTextDocument>
#include <QtGui/QTextCharFormat>
#include <QtGui/QSyntaxHighlighter>
#include <QtGui/QListWidget>
#include <QtGui/QDockWidget>
using namespace std;

class FanucCustom: public QSyntaxHighlighter
{

    public:
        enum
        {
            NormalState = -1,
            CustomMakroComment,
            SubroutineCall,
            IFCondition,
            Symbolic,
            Variable,
            PCodeVar,
            Digit,
            IFVariable,
            IFSymbolic,
            IFDigit,
            LineNumber,
            IFCompare,
            IFCalcVar,
            compareNormal,
            compareSymbolic,
            compareVariable,
            compareDigit,
            Jump,
            Calc,
            Result,
            resultVar,
            resultRet,
            GComment,
            MComment,
            Axis,Feed
        };
        FanucCustom(QTextDocument* document) :
                QSyntaxHighlighter(document)
        {
            QRegExp var("^#\\d+");
            QRegExp sym("^\\[#\\w+\\]$");
            QRegExp math("[\\+\\-\\*\\/]");

            var.setPatternSyntax(QRegExp::RegExp);
            sym.setPatternSyntax(QRegExp::RegExp);
            math.setPatternSyntax(QRegExp::RegExp);

        }
        void setOutline(QListWidget *o)
        {
            this->outline = o;
        }
        void highlightBlock(const QString &text);
        QList<QString> getLineNumbers()
        {
            return lineNumbers;
        }
        ~FanucCustom()
        {
        }

    private:
        QListWidget *outline;
        QList<QString> lineNumbers;
        int numberLength;
        bool compare(QString sringCompare, int startCompare);
        bool calculate(QString str, int startStr);
        void ifCondit(QString sringIF, int lineCol);
        bool checkJump(int startAfterGoto, QString nmb);
        int chkKindOfVar(QString var);

};

#endif /* EDITOR_H_ */
