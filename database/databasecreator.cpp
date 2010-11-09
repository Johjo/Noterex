#include "databasecreator.h"

#include <QSqlQuery>
#include <QFileDialog>


DatabaseCreator::DatabaseCreator(QSqlDatabase db):
        database(db),
        filename("")
{}

DatabaseCreator::DatabaseCreator(QString filename):
        database(QSqlDatabase::addDatabase("QSQLITE", "new")),
        filename(filename)
{}

DatabaseCreator::~DatabaseCreator() {
    database.close();
    QSqlDatabase::removeDatabase("new");
}

void DatabaseCreator::create() {
    openDatabaseIfNecessary();

    if (database.isOpen()) {
        createNote();
        createIndex();
        createTagAndFillIt();

        database.close();
    }
}

void DatabaseCreator::openDatabaseIfNecessary() {
    if (!database.isOpen()) {
        if (! filename.isEmpty()) {
            database.setDatabaseName(filename);
            database.open();
        }
    }
}

void DatabaseCreator::createNote() {
    QSqlQuery query(database);

    query.exec("CREATE TABLE IF NOT EXISTS note (note_id INTEGER PRIMARY KEY AUTOINCREMENT, note_subject TEXT, note_body TEXT, note_keywords TEXT)");
}

void DatabaseCreator::createIndex() {
    QSqlQuery query(database);
    query.exec("CREATE TABLE IF NOT EXISTS index_table (table_id INTEGER PRIMARY KEY AUTOINCREMENT, table_name VARCHAR(15));");
    query.exec("CREATE TABLE IF NOT EXISTS index_keyword (keyword_id INTEGER PRIMARY KEY AUTOINCREMENT, keyword_word VARCHAR(30));");
    query.exec("CREATE TABLE IF NOT EXISTS index_field (field_id INTEGER PRIMARY KEY AUTOINCREMENT, field_name VARCHAR(30));");
    query.exec("CREATE TABLE IF NOT EXISTS index_index (table_id INTEGER, document_id INTEGER, field_id INTEGER, keyword_id INTEGER, index_occurrence INTEGER);");
}

void DatabaseCreator::createTagAndFillIt() {
    createTag();
    fillTag();
}

void DatabaseCreator::createTag() {
    QSqlQuery query(database);
    query.exec("CREATE TABLE IF NOT EXISTS tag (tag_id VARCHAR(5) PRIMARY KEY, tag_name VARCHAR(15));");
    query.exec("CREATE TABLE IF NOT EXISTS note_tag (tag_id INTEGER, note_id INTEGER, tag_value VARCHAR(20), tag_state INTEGER;");
}

void DatabaseCreator::fillTag() {
    QSqlQuery query(database);

    QStringList tags;
    tags << "NEW";

    foreach(QString tag, tags) {
        query.exec("select tag_id from tag where tag_id = '" + tag + "'");
        if (! query.next()) {
            query.exec("insert into tag (tag_id) VALUES ('" + tag + "');");
        }
    }
}

