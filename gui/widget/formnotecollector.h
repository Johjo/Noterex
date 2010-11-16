#ifndef FORMNOTECOLLECTOR_H
#define FORMNOTECOLLECTOR_H

#include <QWidget>
#include <QModelIndex>

#include "note/notedistributor.h"
#include "note/notedao.h"
#include "note/note.h"

namespace Ui {
    class formNoteCollector;
}

class FormNoteCollector : public QWidget
{
    Q_OBJECT

public:
    explicit FormNoteCollector(QWidget *parent = 0);
    ~FormNoteCollector();

public slots:
    void createNote();
    void removeNote();

    void noteChanged();
    void noteSelected(QModelIndex);

private:
    Ui::formNoteCollector *ui;
    NoteDAO * noteDAO;
    NoteDistributor * distributor;

    void createNoteDistributor();
    Note * note;
    bool eventFilter(QObject *, QEvent *);

};

#endif // FORMNOTECOLLECTOR_H
