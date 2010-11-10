#include "searchnotedistributor.h"

#include <QSqlRecord>
#include <QList>

#include "index/searcher.h"
#include "index/standardsearcher.h"


SearchNoteDistributor::SearchNoteDistributor(QString searchedText, NoteDAO *noteDAO, QSqlDatabase db):
        NoteDistributor(),
        database(db),
        searchedText(searchedText),
        noteDAO(noteDAO)
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


Note * SearchNoteDistributor::getNoteFromRow(int row) {
    return noteDAO->get(notesId.at(row));
}
