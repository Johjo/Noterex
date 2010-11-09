#include "content.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

Content::Content():
        QObject(0)
{}

Content::Content(QSqlDatabase database):
        QObject(0),
        id(-1),
        currentMode(Content::New),
        database(database)
{}

Content::Content(int id, QSqlDatabase database):
        QObject(0),
        database(database)
{
    QSqlQuery query("SELECT basketId, body, row, column  FROM content WHERE id = " + QString::number(id), database);

    if (query.next()) {
        this->id = id;
        this->basketId = query.value(0).toInt();
        this->body = query.value(1).toString();
        this->row = query.value(2).toInt();
        this->column = query.value(2).toInt();
        currentMode = NoChange;
    } else {
        this->id = -1;
        currentMode = New;
    }
}

int Content::getId() const {
    return id;
}

int Content::getRow() const {
    return row;
}

int Content::getColumn() const {
    return column;
}

QString Content::getBody() const {
    return body;
}

void Content::setId(int id) {
    this->id = id;
}

void Content::setRow(int row) {
    if (this->row != row) {
        this->row = row;
        if (currentMode == NoChange)
            currentMode = Edited;

    }
}

int Content::getBasketId() const {
    return basketId;
}

void Content::setBasketId(int basketId) {
    if (this->basketId != basketId) {
        this->basketId = basketId;
        if (currentMode == NoChange)
            currentMode = Edited;
    }
}




void Content::setcolumn(int column) {
    if (this->column != column) {
        this->column = column;
        if (currentMode == NoChange)
            currentMode = Edited;

    }
}

void Content::setBody(QString body) {
    if (this->body != body) {
        this->body = body;
        if (currentMode == NoChange)
            currentMode = Edited;
    }
}

bool Content::operator==(const Content &n2) {
    return this->body == n2.body;
}

Content::Mode Content::getCurrentMode() const{
    return currentMode;
}

void Content::save() {
    if (body.trimmed() != "") {
        if (currentMode != NoChange)
            save(database);
    } else {
        remove();
    }
}

void Content::save(QSqlDatabase db) {
    database = db;
    QSqlQuery query(db);

    if (currentMode == New || currentMode == Deleted){
        query.prepare("INSERT INTO content (basketId,body,row,column) VALUES (:basketId, :body, :row, :column)");
    } else if (currentMode == Edited) {
        query.prepare ("UPDATE content set basketId = :basketId, body = :body, row = :row, column = :column where id = :id");
    }

    query.bindValue(":id", id);
    query.bindValue(":basketId", basketId);
    query.bindValue(":body", body);
    query.bindValue(":row", row);
    query.bindValue(":column", column);
    query.exec();

    if (currentMode == New || currentMode == Deleted){
        id = query.lastInsertId().toInt();
    }

    currentMode = NoChange;
}

void Content::remove() {
    if (currentMode == NoChange || currentMode == Edited) {
        QSqlQuery query(database);
        query.prepare("DELETE FROM content where id = :id");
        query.bindValue(":id", id);
        query.exec();
    }
    currentMode = Deleted;
}

void Content::createTable(QSqlDatabase db) {
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS content (id INTEGER PRIMARY KEY AUTOINCREMENT, basketId integer, row integer, column integer, body TEXT);");
}
