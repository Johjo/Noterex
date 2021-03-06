#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QSharedData>

#include "notedata.h"
#include "tag.h"



class Note : public QSharedData{
public:

    typedef QSharedPointer<Note> SharedPointor;

    Note(NoteData * data = 0):data(data){}
    virtual ~Note() {delete data;}

    virtual QString getSubject() const {return data->getSubject();}
    virtual QString getBody() const {return data->getBody();}
    virtual QString getKeywords() const {return data->getKeywords();}

    virtual void setSubject(QString subject) {data->setSubject(subject);}
    virtual void setBody(QString body) {data->setBody(body);}
    virtual void setKeywords(QString keywords) {data->setKeywords(keywords);}

    virtual void save() = 0;
    virtual void remove() = 0;

    virtual int getId() = 0;
    virtual void setId(int id) = 0;

    NoteData * getData() {return data;}

    QList<Tag> getTags() {return data->getTags();}
    void resetTags(){data->resetTags();}
    void addTag(Tag tag){data->addTag(tag);}

private:
    NoteData * data;

};

#endif // NOTE_H
