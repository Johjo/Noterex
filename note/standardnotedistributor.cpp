#include "standardnotedistributor.h"

#include <QSqlRecord>

StandardNoteDistributor::StandardNoteDistributor(QSqlDatabase db):
        NoteDistributor(),
        database(db),
        model(new QSqlQueryModel()),
        factory(db),
        numberOfRows(0)
{
}


StandardNoteDistributor::~StandardNoteDistributor() {
    delete model;
}

void StandardNoteDistributor::refresh() {
    model->setQuery("select note_id from note order by note_id",database);
    while (model->canFetchMore()) {
        model->fetchMore();
    }
    numberOfRows = model->rowCount();
}

int StandardNoteDistributor::count() const{
    return numberOfRows;
}

NoteDB * StandardNoteDistributor::getNoteFromRow(int row) {
    return factory.getNote(model->record(row).value(0).toInt());
}

NoteDistributor * StandardNoteDistributor::createDistributor(QSqlDatabase db) {
    NoteDistributor * distributor = new StandardNoteDistributor(db);
    distributor->refresh();
    return distributor;
}
