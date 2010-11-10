#ifndef NOTEDAO_H
#define NOTEDAO_H

#include "note.h"

#include "notedistributor.h"

class NoteDistributor;

class NoteDAO
{
public:
    NoteDAO() {}
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

};

#endif // NOTEDAO_H
