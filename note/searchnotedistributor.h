#ifndef SEARCHNOTEDISTRIBUTOR_H
#define SEARCHNOTEDISTRIBUTOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QList>

#include "notefactory.h"

#include "notedistributor.h"

class SearchNoteDistributor : public NoteDistributor
{
public:
    virtual ~SearchNoteDistributor();

    virtual int count() const;
    virtual NoteDB * getNoteFromRow(int row);

    virtual void refresh();

    static NoteDistributor * createDistributor(QString searchedText, QSqlDatabase db = QSqlDatabase::database("noterex"));

protected:
    SearchNoteDistributor(QString searchedText, QSqlDatabase db = QSqlDatabase::database("noterex"));

private:
    QSqlDatabase database;
    NoteFactory factory;
    QList<int> notesId;
    QString searchedText;


};

#endif // SEARCHNOTEDISTRIBUTOR_H
