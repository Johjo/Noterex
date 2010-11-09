#include "document.h"

#include <QStringList>
#include <QDebug>

#include <QSqlQuery>

#include "tokenizer.h"

bool Document::tableIsCreated = false;

Document::Document()
{}

Document::Document(QString table, int id):
    table(table),
    id(id)
{}


void Document::add(QString fieldName, QVariant value) {
    valuesMap[fieldName] = value.toString();
}

void Document::save(QSqlDatabase db) {
    deletePreviousIndex(db);
    addCurrentIndex(db);
}

void Document::deletePreviousIndex(QSqlDatabase db) {
    Document::createTableIfNecessary(db);

    QSqlQuery query(db);
    query.prepare("delete from index_index where document_id = :document_id and table_id = :table_id");
    query.bindValue(":document_id ", id);
    query.bindValue(":table_id ", getTableId(db));
    query.exec();
}

void Document::addCurrentIndex(QSqlDatabase db) {
    Document::createTableIfNecessary(db);
    QSqlQuery query(db);
    query.prepare("insert into index_index (table_id, document_id, field_id, keyword_id, index_occurrence) VALUES (:table_id,:document_id,:field_id,:keyword_id,:index_occurrence)");

    Tokenizer::Pointor tokenizer;
    tokenizer = createTokeniser();

    QMapIterator<QString, QString> i(valuesMap);

    db.transaction();
    while (i.hasNext()) {
        i.next();

        int occurrence = 0;


        QStringList list = tokenizer->prepare(i.value());
        foreach (QString word, list) {
            query.bindValue(":table_id",getTableId(db));
            query.bindValue(":document_id", id);
            query.bindValue(":field_id", getFieldId(i.key(),db));
            query.bindValue(":keyword_id", getKeywordId(word,db));
            query.bindValue(":index_occurrence", occurrence);
            query.exec();
            occurrence ++;
        }
    }
    db.commit();
}


Tokenizer * Document::createTokeniser() {
    return new Tokenizer();
}

int Document::getTableId(QSqlDatabase db) {
    if (! tablesMap.contains(table)) {
        QSqlQuery query("select table_id from index_table where table_name = '" + table + "'", db);
        if (query.next()) {
            tablesMap[table] = query.value(0).toInt();
        } else {
            query.exec("insert into index_table (table_name) VALUES('" + table +"')");
            tablesMap[table] = query.lastInsertId().toInt();
        }
    }

    return tablesMap[table];
}


int Document::getFieldId(QString field, QSqlDatabase db)  {
    if (! fieldsMap.contains(field)) {
        QSqlQuery query("select field_id from index_field where field_name = '" + field + "'", db);
        if (query.next()) {
            fieldsMap[field] = query.value(0).toInt();
        } else {
            query.exec("insert into index_field (field_name) VALUES('" + field +"')");
            fieldsMap[field] = query.lastInsertId().toInt();
        }
    }

    return fieldsMap[field];
}

int Document::getKeywordId(QString keyword, QSqlDatabase db) {
    if (! keywordsMap.contains(keyword)) {
        QSqlQuery query("select keyword_id from index_keyword where keyword_word = '" + keyword + "'", db);
        if (query.next()) {
            keywordsMap[keyword] = query.value(0).toInt();
        } else {
            query.exec("insert into index_keyword (keyword_word) VALUES('" + keyword +"')");
            keywordsMap[keyword] = query.lastInsertId().toInt();
        }
    }

    return keywordsMap[keyword];
}

void Document::createTableIfNecessary(QSqlDatabase db) {
    if (! Document::tableIsCreated) {
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS index_table (table_id INTEGER PRIMARY KEY AUTOINCREMENT, table_name VARCHAR(15));");
        query.exec("CREATE TABLE IF NOT EXISTS index_keyword (keyword_id INTEGER PRIMARY KEY AUTOINCREMENT, keyword_word VARCHAR(30));");
        query.exec("CREATE TABLE IF NOT EXISTS index_field (field_id INTEGER PRIMARY KEY AUTOINCREMENT, field_name VARCHAR(30));");
        query.exec("CREATE TABLE IF NOT EXISTS index_index (table_id INTEGER, document_id INTEGER, field_id INTEGER, keyword_id INTEGER, index_occurrence INTEGER);");

        Document::tableIsCreated = true;
    }
}

void Document::remove(QSqlDatabase db) {
    deletePreviousIndex(db);
}
