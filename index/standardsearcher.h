#ifndef STANDARDSEARCHER_H
#define STANDARDSEARCHER_H

#include <QString>
#include <QStringList>
#include <QList>

#include "searcher.h"
#include "note/tag.h"

class StandardSearcher : public Searcher
{
public:
    StandardSearcher(QString table, QString searchedText, QSqlDatabase db = QSqlDatabase::database("noterex"));
    virtual QSet<int> getAllDocuments();

protected:
    StandardSearcher();

private:
    QList<int> getWordsId(QStringList list);
    QSqlDatabase database;
};

#endif // STANDARDSEARCHER_H
