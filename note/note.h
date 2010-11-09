#ifndef NOTE_H
#define NOTE_H

#include <QString>

#include "notedata.h"

class Note {
public:
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

protected:
    NoteData * getData() {return data;}

private:
    NoteData * data;

};

#endif // NOTE_H
