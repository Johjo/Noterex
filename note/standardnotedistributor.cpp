#include "standardnotedistributor.h"

#include <QSqlRecord>
#include <QDebug>

StandardNoteDistributor::StandardNoteDistributor(NoteDAO *noteDAO, QSqlDatabase db):
        NoteDistributor(),
        database(db),
        model(new QSqlQueryModel()),
        numberOfRows(0),
        noteDAO(noteDAO)
{}


StandardNoteDistributor::~StandardNoteDistributor() {
    delete model;
}

void StandardNoteDistributor::refresh() {
    model->setQuery("select note_id from note order by note_id",database);
    while (model->canFetchMore()) {
        model->fetchMore();
    }
    numberOfRows = model->rowCount();

    emit dataChanged();
}

int StandardNoteDistributor::count() const{
    return numberOfRows;
}

Note* StandardNoteDistributor::getNoteFromRow(int row) {
    return noteDAO->get(model->record(row).value(0).toInt());
}
