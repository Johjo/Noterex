#ifndef STANDARDNOTEDISTRIBUTOR_H
#define STANDARDNOTEDISTRIBUTOR_H

#include <QSqlQueryModel>
#include <QSqlDatabase>

#include "notedistributor.h"
#include "notefactory.h"

class StandardNoteDistributor : public NoteDistributor
{
public:
    virtual ~StandardNoteDistributor();

    virtual int count() const;
    virtual NoteDB * getNoteFromRow(int row);

    virtual void refresh();

    static NoteDistributor * createDistributor(QSqlDatabase db = QSqlDatabase::database("noterex"));

protected:
    StandardNoteDistributor(QSqlDatabase db = QSqlDatabase::database("noterex"));

private:
    QSqlDatabase database;
    QSqlQueryModel * model;
    NoteFactory factory;
    int numberOfRows;
};

#endif // STANDARDNOTEDISTRIBUTOR_H
