#include "standardsearcher.h"

#include <QSqlQuery>
#include <QList>
#include <QVariant>
#include <QSet>

#include "tokenizer.h"



StandardSearcher::StandardSearcher():
        Searcher()
{}


StandardSearcher::StandardSearcher(QString table, QString searchedText, QSqlDatabase db):
        Searcher(table, searchedText),
        database(db)
{
}

QList<int> StandardSearcher::getAllDocuments() {
    QList<int> wordsId = getWordsId(Tokenizer().prepare(getSearchedText()));

    QSqlQuery query(database);

    QSet<int> documentsId;
    bool firstTime = true;

    query.prepare("select distinct document_id from index_index where keyword_id = :keyword_id");

    foreach(int keywordId, wordsId) {
        query.bindValue(":keyword_id", keywordId);
        query.exec();

        QSet<int> ids;

        while(query.next()) {
            int documentId = query.value(0).toInt();
            if (! ids.contains(documentId)) {
                ids << documentId;
            }
        }

        if (firstTime) {
            documentsId.unite(ids);
            firstTime = false;
        } else {
            documentsId.intersect(ids);
        }
    }

    return documentsId.toList();
}

QList<int> StandardSearcher::getWordsId(QStringList words) {
    QList<int> wordsId;

    QSqlQuery query(database);
    query.prepare("select keyword_id from index_keyword where  keyword_word = :word");

    foreach(QString word, words) {
        query.bindValue(":word",word);
        query.exec();
        if (query.next()) {
            wordsId << query.value(0).toInt();
        }
    }

    return wordsId;
}
