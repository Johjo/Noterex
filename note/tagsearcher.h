#ifndef TAGSEARCHER_H
#define TAGSEARCHER_H

#include <QSqlDatabase>
#include <QList>

#include "tag.h"


class TagSearcher
{
public:
    TagSearcher(Tag::List tags,  QSqlDatabase db = QSqlDatabase::database("noterex"));

    QSet<int> getAllNotes();

private:
    TagSearcher();

    Tag::List tags;
    QSqlDatabase database;
};

#endif // TAGSEARCHER_H
