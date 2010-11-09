#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <QString>
#include <QStringList>
#include <QSharedData>

class Tokenizer:  public QSharedData
{
public:
    typedef QExplicitlySharedDataPointer<Tokenizer> Pointor;

    Tokenizer();

    QStringList prepare(QString value);

    static QString removeAccents(QString string);


};

#endif // TOKENIZER_H
