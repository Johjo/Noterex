#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <QSqlDatabase>
#include <QSqlQueryModel>

#include "notedb.h"

class NoteFactory
{
public:
    NoteFactory(QSqlDatabase db = QSqlDatabase::database("noterex"));

    virtual ~NoteFactory();

    NoteDB * createNote();
    NoteDB * getNote(int id);

    int count() const;

private:
    QSqlDatabase database;
};

#endif // NOTEFACTORY_H
