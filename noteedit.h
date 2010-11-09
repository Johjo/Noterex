#ifndef NOTEEDIT_H
#define NOTEEDIT_H

#include <QTextEdit>

#include "data\content.h"

class NoteEdit : public QTextEdit
{
    Q_OBJECT
public:
    NoteEdit(QWidget *parent, Content * content);

public slots:
    void s_textChanged();    
    void s_contextMenu(const QPoint &pos);

signals:
    void textChanged(QString);
    void editingFinished();
    void deleteEdit();

protected:
    void focusOutEvent(QFocusEvent *e);
    void resizeWithText();

private:
    Content * content;
    NoteEdit();
};

#endif // NOTEEDIT_H
