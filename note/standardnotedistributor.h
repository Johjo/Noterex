#ifndef STANDARDNOTEDISTRIBUTOR_H
#define STANDARDNOTEDISTRIBUTOR_H

#include <QSqlQueryModel>
#include <QSqlDatabase>

#include "application.h"
#include "notedistributor.h"
#include "notedao.h"

class StandardNoteDistributor : public NoteDistributor
{
public:
    StandardNoteDistributor(NoteDAO * noteDAO = Application::getApplication()->getNoteDAO(), QSqlDatabase db = QSqlDatabase::database("noterex"));
    virtual ~StandardNoteDistributor();

    virtual int count() const;
    virtual Note * getNoteFromRow(int row);

    virtual void refresh();

private:
    QSqlDatabase database;
    QSqlQueryModel * model;
    int numberOfRows;
    NoteDAO * noteDAO;

};

#endif // STANDARDNOTEDISTRIBUTOR_H
