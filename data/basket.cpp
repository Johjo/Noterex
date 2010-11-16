#include "basket.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include "basketroot.h"

// ================
// = Constructor =
// ================
Basket::Basket() {}

Basket::Basket(QSqlDatabase database):
        database(database),
        id(-1)
{
    init();
}

Basket::Basket(int id, QSqlDatabase database):
        database(database),
        id(id)
{
    init();
}

// ===========
// = getters =
// ===========

int Basket::getId() {
    return id;
}

int Basket::getParentId() {
    return parentId;
}

int Basket::getRow() {
    return row;
}

bool Basket::hasChild(int row) {
    return countChild() >= row + 1;
}

QExplicitlySharedDataPointer<Basket> Basket::getChild(int row) {
    QList<int> list = getChildrenId();

    QExplicitlySharedDataPointer<Basket> basket;
    basket = new Basket(list.value(row, -1), database);

    return basket;
}

Basket::Mode Basket::getCurrentMode() {
    return currentMode;
}

QExplicitlySharedDataPointer<Basket> Basket::getParent() {
    QExplicitlySharedDataPointer<Basket> basket;

    if (parentId > 0) {
        basket = new Basket(parentId,database);
    } else {
        basket = new BasketRoot(database);
    }

    return basket;
}

QString Basket::getTitle() {
    return title;
}

bool Basket::isRoot() {
    return id == 0;
}

bool Basket::hasParent() {
    return parentId > 0;
}

int Basket::countContent() {
    QSqlQuery query("SELECT count(*) FROM content WHERE basketId = " + QString::number(id), database);

    query.next();
    return query.value(0).toInt();
}

QExplicitlySharedDataPointer<Content> Basket::getContent(int row) {
    QSqlQuery query("SELECT id, row FROM content WHERE basketId = " + QString::number(id) + " order by row", database);

    QList<int> ids;

    while (query.next()) {
        ids << query.value(0).toInt();
    }

    QExplicitlySharedDataPointer<Content> content ;

    if (ids.count() <= row) {
        content = new Content(database);
    } else {
        content = new Content(ids.at(row),database);
    }

    content->setBasketId(this->getId());

    return content;
}


// ===========
// = Setters =
// ===========

void Basket::setParentId(int id) {
    this->parentId = id;
    if (this->currentMode == NoChange)
        this->currentMode = Edited;
}

void Basket::setTitle(QString title) {
    this->title = title;
    if (this->currentMode == NoChange)
        this->currentMode = Edited;
}

void Basket::setRow(int row) {
    this->row = row;
}

// ===========
// = Méthods =
// ===========

void Basket::init() {
    QSqlQuery query("SELECT title, row, parentId FROM basket WHERE id = " + QString::number(id), database);

    query.exec();
    if (query.next()) {
        this->title = query.value(0).toString();
        this->row = query.value(1).toInt();
        this->parentId = query.value(2).toInt();
        currentMode = NoChange;
    } else if (! isRoot()){
        this->id = -1;
        this->row = 0;
        this->parentId = -1;
        currentMode = New;
    } else {
        this->title = QObject::tr("root");
        this->row = 0;
        this->parentId = -1;
        currentMode = New;
    }
}

int Basket::countChild() {
    QList<int> list = getChildrenId();

    return list.count();
}

void Basket::save(QSqlDatabase db) {
    QSqlQuery query(db);

    if (currentMode == New || currentMode == Deleted){
        if (isRoot()){
            query.prepare("INSERT INTO basket (id, parentId, title) VALUES (:id, :parentId, :title)");
        } else {
            query.prepare("INSERT INTO basket (parentId, title) VALUES (:parentId, :title)");
        }

    } else if (currentMode == Edited) {
        query.prepare ("UPDATE basket set parentId = :parentId, title = :title where id = :id");
    }
    query.bindValue(":id", id);
    query.bindValue(":parentId", this->parentId);
    query.bindValue(":title", this->title);
    query.exec();

    if (currentMode == New || currentMode == Deleted){
        id = query.lastInsertId().toInt();
    }

    currentMode = NoChange;
}

void Basket::save() {
    save(database);
}

QList<int> Basket::getChildrenId() {
    QSqlQuery query("SELECT id, parentId, row FROM basket WHERE parentId = " + QString::number(id) + " order by row", database);

    QList<int> list;

    while(query.next()) {
        list << query.value(0).toInt();
    }

    return list;
}

QSqlDatabase Basket::getDatabase(){
    return database;
}

void Basket::clearNote() {
    QSqlQuery query;
    query.prepare("delete from content WHERE basketId = :basketId");
    query.bindValue(":basketId", id);
    query.exec();
}

QExplicitlySharedDataPointer<Content> Basket::addNote() {
    QExplicitlySharedDataPointer<Content> content;

    content = new Content(database);
    content->setBasketId(id);

    return content;
}

void Basket::addNote(QStringList list) {
    int i = 0;

    database.transaction();
    foreach(QString body, list) {
        if (! body.isEmpty()) {
            Content content(database);
            content.setBasketId(id);
            content.setRow(i);
            content.setBody(body);
            content.save();

            i ++;
        }
    }
    database.commit();
}

void Basket::remove() {
    database.transaction();
    QSqlQuery query;
    query.prepare("delete from Basket where id = :id");
    query.bindValue(":id",id);
    query.exec();
    query.prepare("delete from content where basketId = :basketId");
    query.bindValue(":basketId",id);
    query.exec();
    database.commit();
}


// ==================
// = Static methods =
// ==================

void Basket::createTable(QSqlDatabase db) {
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS basket (id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT, parentId integer, row integer);");
}


