#include "notedata.h"

NoteData::NoteData(QString subject, QString body, QString keywords):
        subject(subject),
        body(body),
        keywords(keywords)
{}


void NoteData::setSubject(QString subject){
    this->subject = subject;
}

void NoteData::setBody(QString body){
    this->body = body;
}

void NoteData::setKeywords(QString keywords) {
    this->keywords = keywords;
}

QString NoteData::getSubject() const{
    return subject;
}

QString NoteData::getBody() const{
    return body;
}

QString NoteData::getKeywords() const{
    return keywords;
}



