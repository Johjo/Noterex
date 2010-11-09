#include "notefactory.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include "notedata.h"
#include "application.h"

NoteFactory::NoteFactory(QSqlDatabase db):
        database(db)
{}


NoteFactory::~NoteFactory() {
}

NoteDB * NoteFactory::createNote() {
    return new NoteDB(database);
}

NoteDB * NoteFactory::getNote(int id) {
    QSqlQuery query(database);

    query.prepare("select note_subject, note_body, note_keywords from note where note_id = :note_id");
    query.bindValue(":note_id", id);
    query.exec();

    if (query.next()) {
        NoteData * np(new NoteData());

        np->setSubject(query.value(0).toString());
        np->setBody(query.value(1).toString());
        np->setKeywords(query.value(2).toString());
        return new NoteDB(np, database,id);
    } else {
        return new NoteDB(database);
    }
}

int NoteFactory::count() const{
    QSqlQuery query("select count(id) from note", database);

    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return 0;
    }
}
