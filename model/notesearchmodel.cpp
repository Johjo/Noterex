#include "notesearchmodel.h"

NoteSearchModel::NoteSearchModel(QObject *parent) :
        QAbstractListModel(parent)
{
}

NoteSearchModel::NoteSearchModel(Searcher * searcher, QObject *parent):
        QAbstractListModel(parent),
        searcher(searcher)
{}

int NoteSearchModel::rowCount(const QModelIndex &parent) const {
    return 0;
}




QVariant NoteSearchModel::data(const QModelIndex & index, int role) const {
    return QVariant();

}

