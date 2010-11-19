#ifndef FORMNOTECOLLECTOR_H
#define FORMNOTECOLLECTOR_H

#include <QWidget>
#include <QModelIndex>

#include "note/notedistributor.h"
#include "note/notedao.h"
#include "note/note.h"
#include "note/notegui.h"

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
    void slotCreateNote();
    void slotBodyChanged();

    void removeNote();

    void slotNoteSelected(QModelIndex);

private:
    Ui::formNoteCollector *ui;
    NoteDAO * noteDAO;
    NoteDistributor * distributor;

    NoteGUI * noteGui;

    void createNoteDistributor();
    bool eventFilter(QObject *, QEvent *);
    Note * createNote();
    void createNoteGui(Note * note);

};

#endif // FORMNOTECOLLECTOR_H
