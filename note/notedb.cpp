#include "notedb.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include "noteindexor.h"

NoteDB::NoteDB(QSqlDatabase db, int id):
        Note(new NoteData()),
        database(db),
        id(id)
{}

NoteDB::NoteDB(NoteData * data, QSqlDatabase db, int id):
        Note(data),
        database(db),
        id(id)
{}

NoteDB::~NoteDB() {
}

void NoteDB::save() {
    QSqlQuery query(database);

    bool mustBeCreated = ! isExisting();

    if (mustBeCreated) {
        query.prepare("INSERT INTO note (note_subject, note_body, note_keywords) VALUES (:subject, :body, :keywords)");
    } else {
        query.prepare ("UPDATE note set note_subject = :subject, note_body = :body, note_keywords = :keywords where note_id = :id");
        query.bindValue(":id", id);
    }

    query.bindValue(":subject", getData()->getSubject());
    query.bindValue(":body", getData()->getBody());
    query.bindValue(":keywords", getData()->getKeywords());

    if (!query.exec()) {
        qDebug() << "can't create or add note" << query.lastError();
    }

    if (mustBeCreated) {
        id = query.lastInsertId().toInt();
    }


    NoteIndexor(this, database).index();
}

bool NoteDB::isExisting() {
    QSqlQuery query(database);

    query.prepare("select note_id from note where note_id = :note_id");
    query.bindValue(":note_id", id);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }


    if (query.next()) {
        return true;
    } else {
        return false;
    }
}

void NoteDB::remove() {
    QSqlQuery query(database);
    query.prepare("DELETE FROM note where note_id = :id");
    query.bindValue(":id", id);
    query.exec();

    NoteIndexor(this, database).removeIndex();
}

int NoteDB::getId(){
    return id;
}
