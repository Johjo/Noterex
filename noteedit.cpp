#include "noteedit.h"

#include <QAbstractTextDocumentLayout>
#include <QMessageBox>
#include <QMenu>
#include <QAction>

NoteEdit::NoteEdit(){}

NoteEdit::NoteEdit(QWidget* parent, Content * content) :
    QTextEdit(parent),
    content(content)
{
    connect(this,SIGNAL(textChanged()),this,SLOT(s_textChanged()));
    connect(this,SIGNAL(textChanged(QString)),content,SLOT(setBody(QString)));
    connect(this,SIGNAL(editingFinished()),content,SLOT(save()));

    setText(content->getBody());

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::WheelFocus);
    resizeWithText();

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(s_contextMenu(const QPoint&)));
}

void NoteEdit::s_contextMenu(const QPoint &pos) {
    QMenu * menu = new QMenu(this);
    menu->addAction(tr("basketcell.delete"),this,SIGNAL(deleteEdit()));
    menu->exec(mapToGlobal(pos));
}

void NoteEdit::resizeWithText() {
    document()->adjustSize();
    QSizeF size = document()->size();

    setMaximumHeight(size.height());
    setMaximumWidth(16777215);
}

void NoteEdit::s_textChanged(){
    resizeWithText();
    emit textChanged(toPlainText());
}

void NoteEdit::focusOutEvent(QFocusEvent *e) {
    if (e->lostFocus()) {
        emit editingFinished();
    }
    QTextEdit::focusOutEvent(e);
}
