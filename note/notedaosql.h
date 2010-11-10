#ifndef NOTEDAOSQL_H
#define NOTEDAOSQL_H

#include <QSqlDatabase>

#include "notedao.h"

class NoteDAOSql : public NoteDAO
{
public:
    NoteDAOSql(QSqlDatabase db = QSqlDatabase::database("noterex"));

    virtual ~NoteDAOSql();

    virtual Note * create();
    virtual Note * get(int id);
    virtual int insert(Note * note);
    virtual bool update(Note * note);
    virtual bool remove(Note * note);
    virtual bool exist(Note * note);

    virtual NoteDistributor * getNoteDistributor();
    virtual NoteDistributor * getNoteDistributor(QString searchedText);


private:
    QSqlDatabase database;

};

#endif // NOTEDAOSQL_H
