#include "tokenizer.h"

#include <QRegExp>


Tokenizer::Tokenizer()
{}

QStringList Tokenizer::prepare(QString value) {
    QString s = Tokenizer::removeAccents(value);

    QRegExp regexp("[^0-9a-zA-Z_]+");

    return s.toLower().split(regexp, QString::SkipEmptyParts);
}

QString Tokenizer::removeAccents(QString s) {
    QString newString = s.normalized(QString::NormalizationForm_KD);;

    int i = 0;
    while (i < newString.size()) {
        if (newString[i].category() == QChar::Mark_NonSpacing) {
            newString.remove(i, 1);
        }
        i ++;
    }

    return newString;
}
