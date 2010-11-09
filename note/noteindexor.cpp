#include "noteindexor.h"

#include "index/document.h"

NoteIndexor::NoteIndexor()
{}

NoteIndexor::NoteIndexor(NoteDB * note, QSqlDatabase database):
        doc("note",note->getId()),
        database(database)
{
    doc.add("subject", note->getSubject());
    doc.add("body", note->getBody());
    doc.add("keywords", note->getBody());
}

void NoteIndexor::index() {
    doc.save(database);
}

void NoteIndexor::removeIndex() {
    doc.remove(database);
}

