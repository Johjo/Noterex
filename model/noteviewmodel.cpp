#include "noteviewmodel.h"

#include "note/notedata.h"
#include "note/notedb.h"

NoteViewModel::NoteViewModel()
{}


NoteViewModel::NoteViewModel(NoteDistributor * distributor, QObject *parent):
        QAbstractListModel(parent),
        distributor(distributor)
{


}

int NoteViewModel::rowCount(const QModelIndex &) const {
    return distributor->count();
}

QVariant NoteViewModel::data(const QModelIndex & index, int role) const {
    if (! index.isValid()) {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
        return QVariant();

    Note * note = distributor->getNoteFromRow(index.row());

    return note->getSubject();
}
