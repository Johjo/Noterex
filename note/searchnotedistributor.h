#ifndef SEARCHNOTEDISTRIBUTOR_H
#define SEARCHNOTEDISTRIBUTOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QList>


#include "application.h"
#include "notedao.h"

#include "notedistributor.h"


class SearchNoteDistributor : public NoteDistributor
{
public:
    SearchNoteDistributor(QString searchedText, NoteDAO * noteDAO = Application::getApplication()->getNoteDAO(), QSqlDatabase db = QSqlDatabase::database("noterex"));

    virtual ~SearchNoteDistributor();

    virtual int count() const;
    virtual Note * getNoteFromRow(int row);

    virtual void refresh();

    static NoteDistributor * createDistributor(QString searchedText, QSqlDatabase db = QSqlDatabase::database("noterex"));

private:
    QSqlDatabase database;
    QString searchedText;
    NoteDAO * noteDAO;
    QList<int> notesId;


};

#endif // SEARCHNOTEDISTRIBUTOR_H
