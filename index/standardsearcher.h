#ifndef STANDARDSEARCHER_H
#define STANDARDSEARCHER_H

#include <QString>
#include <QStringList>

#include "searcher.h"

class StandardSearcher : public Searcher
{
public:
    StandardSearcher(QString table, QString searchedText, QSqlDatabase db = QSqlDatabase::database("noterex"));

    virtual QList<int> getAllDocuments();

protected:
    StandardSearcher();

private:
    QList<int> getWordsId(QStringList list);
    QSqlDatabase database;
};

#endif // STANDARDSEARCHER_H
