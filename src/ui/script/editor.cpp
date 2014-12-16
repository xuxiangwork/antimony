#include <Python.h>

#include <QDebug>

#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QHelpEvent>
#include <QToolTip>

#include "graph/datum/datums/script_datum.h"

#include "ui/script/editor.h"
#include "ui/script/syntax.h"
#include "ui/util/colors.h"

ScriptEditor::ScriptEditor(ScriptDatum* datum, QWidget* parent)
    : QPlainTextEdit(parent), datum(datum)
{
    QFont font;
    font.setFamily("Courier");
    document()->setDefaultFont(font);

    new SyntaxHighlighter(document());
    //document()->setDefaultTextColor(Colors::base04);

    connect(document(), &QTextDocument::contentsChanged,
            this, &ScriptEditor::onTextChanged);
    connect(datum, &Datum::changed,
            this, &ScriptEditor::onDatumChanged);
    connect(datum, &Datum::destroyed,
            parent, &QWidget::deleteLater);

    onDatumChanged(); // update tooltip and text
}

void ScriptEditor::onTextChanged()
{
    setToolTip("");
    QToolTip::hideText();
    if (datum)
        datum->setExpr(document()->toPlainText());
}

void ScriptEditor::onDatumChanged()
{
    if (datum)
    {
        if (!datum->getValid())
        {
            setToolTip(datum->getErrorTraceback());
        }
        else
        {
            setToolTip("");
            QToolTip::hideText();
        }

        if (datum->getExpr() != document()->toPlainText())
            document()->setPlainText(datum->getExpr());
    }
    else
    {
        setToolTip("");
        QToolTip::hideText();
    }
}
