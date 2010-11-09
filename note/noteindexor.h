#ifndef NOTEINDEXOR_H
#define NOTEINDEXOR_H

#include <QSqlDatabase>

#include "notedb.h"
#include "index/document.h"

class NoteIndexor
{
public:
    NoteIndexor(NoteDB * note, QSqlDatabase = QSqlDatabase::database("noterex"));
    void index();
    void removeIndex();

protected:
    NoteIndexor();

private:
    Document doc;
    QSqlDatabase database;
};

#endif // NOTEINDEXOR_H
