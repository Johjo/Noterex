#include "searchnotedistributor.h"

#include <QSqlRecord>
#include <QList>
#include <QDebug>

#include "index/searcher.h"
#include "index/standardsearcher.h"

#include "tagsearcher.h"


SearchNoteDistributor::SearchNoteDistributor(QString searchedText, NoteDAO *noteDAO, QSqlDatabase db):
        NoteDistributor(),
        database(db),
        searchedText(searchedText),
        noteDAO(noteDAO)
{}

SearchNoteDistributor::SearchNoteDistributor(QString searchedText, Tag tag, NoteDAO *noteDAO, QSqlDatabase db):
        NoteDistributor(),
        database(db),
        searchedText(searchedText),
        noteDAO(noteDAO)
{
    tags.append(tag);
}

SearchNoteDistributor::SearchNoteDistributor(QString searchedText, QList<Tag> tags, NoteDAO *noteDAO, QSqlDatabase db):
        NoteDistributor(),
        database(db),
        searchedText(searchedText),
        noteDAO(noteDAO),
        tags(tags)
{}




SearchNoteDistributor::~SearchNoteDistributor() {
}

void SearchNoteDistributor::refresh() {
    QSet<int> documentsId;

    bool firstSelection = true;

    if (! searchedText.trimmed().isEmpty()) {
        if (firstSelection) {
            documentsId.unite(getNotesIdFromSearchedText());
            firstSelection = false;
        } else {
            documentsId.intersect(getNotesIdFromSearchedText());
        }
    }

    if (! tags.isEmpty()) {
        if (firstSelection) {
            documentsId.unite(getNotesIdFromTag());
            firstSelection = false;
        } else {
            documentsId.intersect(getNotesIdFromTag());
        }
    }
    notesId.clear();
    notesId = documentsId.toList();

    emit dataChanged();
}

QSet<int> SearchNoteDistributor::getNotesIdFromTag() {
    TagSearcher searcher(tags,database);

    return searcher.getAllNotes();
}

QSet<int> SearchNoteDistributor::getNotesIdFromSearchedText() {
    StandardSearcher searcher("note",searchedText,database);

    return searcher.getAllDocuments();
}

int SearchNoteDistributor::count() const{
    return notesId.count();
}


Note * SearchNoteDistributor::getNoteFromRow(int row) {
    if (row >= notesId.count()) {
        return noteDAO->create();
    } else {
        return noteDAO->get(notesId.at(row));
    }
}
