#ifndef NOTEDAO_H
#define NOTEDAO_H

#include <QObject>

#include "note.h"

#include "notedistributor.h"
#include "tag.h"

class NoteDistributor;

class NoteDAO : public QObject
{
    Q_OBJECT
public:
    NoteDAO(QObject *parent = 0);
    virtual ~NoteDAO() {}

    virtual Note * create() = 0;
    virtual Note * get(int id) = 0;
    virtual int insert(Note * note) = 0;
    virtual bool update(Note * note) = 0;
    virtual bool remove(Note * note) = 0;
    virtual bool exist(Note * note) = 0;

    bool save(Note * note) {
        if (exist(note)) {
            return update(note);
        } else {
            return insert(note);
        }
    }

    virtual NoteDistributor * getNoteDistributor() = 0;
    virtual NoteDistributor * getNoteDistributor(QString searchedText) = 0;
    virtual NoteDistributor * getNoteDistributor(QList<Tag> tags, QString searchedText = "") = 0;

signals:
    void dataChanged();

};

#endif // NOTEDAO_H
