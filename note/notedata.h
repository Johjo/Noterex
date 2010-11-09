#ifndef NOTEDATA_H
#define NOTEDATA_H

#include <QString>
#include <QSharedData>
#include <QSharedPointer>


class NoteData : public QSharedData
{
public:
    typedef QSharedPointer<NoteData> SharedPointer;

    NoteData(QString subject = "", QString body = "", QString keywords = "");

    QString getSubject() const;
    QString getBody() const;
    QString getKeywords() const;

    void setSubject(QString);
    void setBody(QString);
    void setKeywords(QString);

private:
    QString subject;
    QString body;
    QString keywords;

};

#endif // NOTEDATA_H
