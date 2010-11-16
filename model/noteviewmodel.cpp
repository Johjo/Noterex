#include "noteviewmodel.h"

#include <QDebug>

#include "note/notedata.h"
#include "note/notedb.h"

NoteViewModel::NoteViewModel()
{}


NoteViewModel::NoteViewModel(NoteDistributor * distributor, QObject *parent):
        QAbstractListModel(parent),
        distributor(distributor)
{
    connect(distributor,SIGNAL(dataChanged()), this,SLOT(refresh()));

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

void NoteViewModel::refresh() {
    emit dataChanged(createIndex(0,0,0), createIndex(rowCount() - 1,0,0));
}
