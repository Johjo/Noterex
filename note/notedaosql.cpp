#include "notedaosql.h"

#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

#include "notedb.h"
#include "noteindexor.h"

#include "standardnotedistributor.h"
#include "searchnotedistributor.h"

NoteDAOSql::NoteDAOSql(QSqlDatabase db):
        NoteDAO(),
        database(db)
{}

NoteDAOSql::~NoteDAOSql(){}

Note * NoteDAOSql::create(){
    return new NoteDB(this);
}

Note * NoteDAOSql::get(int id){
    QSqlQuery query(database);

    query.prepare("select note_subject, note_body, note_keywords from note where note_id = :note_id");
    query.bindValue(":note_id", id);
    query.exec();

    if (query.next()) {
        NoteData * np(new NoteData());

        np->setSubject(query.value(0).toString());
        np->setBody(query.value(1).toString());
        np->setKeywords(query.value(2).toString());

        getTagsForNote(np, id);
        return new NoteDB(np, this,id);
    } else {
        return new NoteDB(this);
    }
}

void NoteDAOSql::getTagsForNote(NoteData * note, int id) {
    note->resetTags();

    QSqlQuery query(database);
    query.exec("select tag_id, tag_state, tag_param from note_tag where note_id = " + QString::number(id));
    while(query.next()) {
        QString tagId = query.value(0).toString();
        int state =  query.value(1).toInt();
        QString param = query.value(2).toString();

        note->addTag(Tag(tagId,state,param));
    }
}



int NoteDAOSql::insert(Note * note){
    QSqlQuery query(database);

    NoteData * data = note->getData();

    query.prepare("INSERT INTO note (note_subject, note_body, note_keywords) VALUES (:subject, :body, :keywords)");
    query.bindValue(":subject", data->getSubject());
    query.bindValue(":body", data->getBody());
    query.bindValue(":keywords", data->getKeywords());

    if (query.exec()) {
        note->setId(query.lastInsertId().toInt());
        NoteIndexor(note, database).index();

        saveTagsForNote(data,note->getId());

        emit dataChanged();

        return true;
    } else {
        qDebug() << "can't insert note" << query.lastError();
        return false;
    }
}

bool NoteDAOSql::update(Note * note){
    QSqlQuery query(database);

    NoteData* data = note->getData();

    query.prepare ("UPDATE note set note_subject = :subject, note_body = :body, note_keywords = :keywords where note_id = :id");
    query.bindValue(":id", note->getId());

    query.bindValue(":subject", data->getSubject());
    query.bindValue(":body", data->getBody());
    query.bindValue(":keywords", data->getKeywords());

    if (query.exec()) {
        NoteIndexor(note, database).index();
        saveTagsForNote(data,note->getId());

        emit dataChanged();

        return true;
    } else {
        qDebug() << "can't update note" << query.lastError();
        return false;
    }
}

void NoteDAOSql::saveTagsForNote(NoteData * noteData, int id) {
    removeTagsForNote(id);
    QSqlQuery query(database);

    query.prepare ("INSERT INTO note_tag (note_id, tag_id, tag_state, tag_param) VALUES (:note_id, :tag_id, :tag_state, :tag_param)");

    foreach(Tag tag, noteData->getTags()) {
        query.bindValue(":note_id", id);
        query.bindValue(":tag_id", tag.getId());
        query.bindValue(":tag_state", tag.getState());
        query.bindValue(":tag_param", tag.getParam());
        query.exec();
    }
}

void NoteDAOSql::removeTagsForNote(int id){
    QSqlQuery query(database);

    query.prepare ("delete from note_tag where note_id = :note_id");
    query.bindValue(":note_id", id);
    query.exec();
}


bool NoteDAOSql::remove(Note * note){
    QSqlQuery query(database);
    query.prepare("DELETE FROM note where note_id = :id");
    query.bindValue(":id", note->getId());
    if (query.exec()) {
        NoteIndexor(note, database).removeIndex();

        removeTagsForNote(note->getId());
        note->setId(-1);

        emit dataChanged();

        return true;
    } else {
        return false;
    }
}

bool NoteDAOSql::exist(Note * note){
    QSqlQuery query(database);

    query.prepare("select note_id from note where note_id = :note_id");
    query.bindValue(":note_id", note->getId());
    if (!query.exec()) {
        qDebug() << query.lastError();
    }

    if (query.next()) {
        return true;
    } else {
        return false;
    }
}



NoteDistributor * NoteDAOSql::getNoteDistributor() {
    NoteDistributor * distributor = new StandardNoteDistributor(this,database);
    distributor->refresh();

    connect(this,SIGNAL(dataChanged()),distributor,SLOT(refresh()));

    return distributor;
}

NoteDistributor * NoteDAOSql::getNoteDistributor(QString searchedText) {
    NoteDistributor * distributor = new SearchNoteDistributor(searchedText,this,database);
    distributor->refresh();

    connect(this,SIGNAL(dataChanged()),distributor,SLOT(refresh()));

    return distributor;
}

NoteDistributor * NoteDAOSql::getNoteDistributor(QList<Tag> tags, QString searchedText) {
    NoteDistributor * distributor = new SearchNoteDistributor(searchedText,tags,this, database);
    distributor->refresh();

    connect(this,SIGNAL(dataChanged()),distributor,SLOT(refresh()));

    return distributor;
}
