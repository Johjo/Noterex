#ifndef NOTEDAOSQL_H
#define NOTEDAOSQL_H

#include <QSqlDatabase>

#include "notedao.h"
#include "tag.h"

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
    virtual NoteDistributor * getNoteDistributor(QList<Tag> tags, QString searchedText = "");

private:
    QSqlDatabase database;

    void getTagsForNote(NoteData *, int id);
    void saveTagsForNote(NoteData *, int id);
    void removeTagsForNote(int id);
};

#endif // NOTEDAOSQL_H
