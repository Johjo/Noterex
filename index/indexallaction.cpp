#include <QApplication>

#include "indexallaction.h"
#include "note/standardnotedistributor.h"
#include "note/noteindexor.h"

IndexAllAction::IndexAllAction(NoteDAO * noteDAO, QObject *parent) :
    QAction(tr("Index all"), parent),
    distributor(noteDAO->getNoteDistributor())
{
    connect(this,SIGNAL(triggered()),this, SLOT(IndexAllDocuments()));
}

IndexAllAction::~IndexAllAction() {
    delete distributor;
}

void IndexAllAction::IndexAllDocuments() {
    QApplication::setOverrideCursor( Qt::WaitCursor );

    for (int i = 0; i < distributor->count(); i ++) {
        NoteIndexor(distributor->getNoteFromRow(i)).index();
    }

    QApplication::restoreOverrideCursor();
}


