#ifndef DATABASECREATOR_H
#define DATABASECREATOR_H

#include <QSqlDatabase>

class DatabaseCreator
{
public:
    DatabaseCreator(QSqlDatabase db = QSqlDatabase::database("noterex"));
    DatabaseCreator(QString filename);
    ~DatabaseCreator();

    void create();

private:
    QSqlDatabase database;
    QString filename;


    void openDatabaseIfNecessary();
    void createNote();
    void createIndex();
    void createTag();

};

#endif // DATABASECREATOR_H
