#ifndef SEARCHER_H
#define SEARCHER_H

#include <QString>
#include <QList>
#include <QSqlDatabase>

class Searcher
{
public:
    Searcher(QString table, QString searchedText):table(table),searchedText(searchedText){}

    virtual QSet<int> getAllDocuments() = 0;

protected:
    Searcher() {}
    QString getTable() {return table;}
    QString getSearchedText() {return searchedText;}

private:
    QString table;
    QString searchedText;
};

#endif // SEARCHER_H
