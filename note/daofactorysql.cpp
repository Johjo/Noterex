#include "daofactorysql.h"

#include "notedaosql.h"

DAOFactorySql::DAOFactorySql(QSqlDatabase db):
        database(db)
{
    noteDAO = new NoteDAOSql(database);
}

NoteDAO * DAOFactorySql::getNoteDAO() {
    return noteDAO;
}
