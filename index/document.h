#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QSqlDatabase>

#include <QString>
#include <QVariant>
#include <QMap>

#include "tokenizer.h"

class Document
{
public:
    Document();
    Document(QString table, int id);

    void add(QString fieldName, QVariant value);
    void save(QSqlDatabase);
    void remove(QSqlDatabase);

    Tokenizer * createTokeniser();

private:
    QString table;
    int id;
    QMap<QString, QString> valuesMap;
    QMap<QString, int> keywordsMap;
    QMap<QString, int> tablesMap;
    QMap<QString, int> fieldsMap;

    void deletePreviousIndex(QSqlDatabase);
    void addCurrentIndex(QSqlDatabase);

    int getTableId(QSqlDatabase);
    int getFieldId(QString, QSqlDatabase);
    int getKeywordId(QString, QSqlDatabase);

    static void createTableIfNecessary(QSqlDatabase);
    static bool tableIsCreated;
};

#endif // DOCUMENT_H
