#ifndef DAOFACTORYSQL_H
#define DAOFACTORYSQL_H


#include <QSqlDatabase>

#include "daofactory.h"

class DAOFactorySql : public DAOFactory
{
public:
    DAOFactorySql(QSqlDatabase db = QSqlDatabase::database("noterex"));

    virtual NoteDAO * getNoteDAO();

private:
    QSqlDatabase database;
    NoteDAO * noteDAO;
};

#endif // DAOFACTORYSQL_H
