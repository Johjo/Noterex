#include "searchnotedistributor.h"

#include <QSqlRecord>
#include <QList>

#include "index/searcher.h"
#include "index/standardsearcher.h"


SearchNoteDistributor::SearchNoteDistributor(QString searchedText,QSqlDatabase db):
        NoteDistributor(),
        database(db),
        factory(db),
        searchedText(searchedText)
{
}


SearchNoteDistributor::~SearchNoteDistributor() {
}

void SearchNoteDistributor::refresh() {
    Searcher * searcher = new StandardSearcher("note",searchedText,database);

    notesId = searcher->getAllDocuments();
}

int SearchNoteDistributor::count() const{
    return notesId.count();
}


NoteDB * SearchNoteDistributor::getNoteFromRow(int row) {
    return factory.getNote(notesId.at(row));
}

NoteDistributor * SearchNoteDistributor::createDistributor(QString searchedText, QSqlDatabase db) {
    NoteDistributor * distributor = new SearchNoteDistributor(searchedText, db);
    distributor->refresh();
    return distributor;
}
