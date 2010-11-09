#ifndef NOTEDB_H
#define NOTEDB_H

#include <QSqlDatabase>

#include "note.h"
#include "notedata.h"


class NoteDB : public Note
{
public:
    NoteDB(QSqlDatabase db = QSqlDatabase::database("noterex"), int id = -1);
    NoteDB(NoteData * data, QSqlDatabase db, int id);

    virtual ~NoteDB();

    virtual void save();
    virtual void remove();

    int getId();


protected:
    virtual bool isExisting();

private:
    QSqlDatabase database;
    int id;
};

#endif // NOTEDB_H
