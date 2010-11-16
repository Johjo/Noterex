#ifndef NOTEDATA_H
#define NOTEDATA_H

#include <QString>
#include <QSharedData>
#include <QSharedPointer>

#include "tag.h"


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

    QList<Tag> getTags();
    void resetTags();
    void addTag(Tag);


private:
    QString subject;
    QString body;
    QString keywords;

    QList<Tag> tags;

};

#endif // NOTEDATA_H
