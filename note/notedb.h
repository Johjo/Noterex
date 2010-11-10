#ifndef NOTEDB_H
#define NOTEDB_H

#include "note.h"
#include "notedata.h"
#include "notedao.h"

class NoteDB : public Note
{
public:
    NoteDB(NoteDAO * noteDAO, int id = -1);
    NoteDB(NoteData * data, NoteDAO * noteDAO, int id);

    virtual ~NoteDB();

    virtual void save();
    virtual void remove();


    int getId();
    void setId(int id);

private:
    NoteDAO * noteDAO;
    int id;
};

#endif // NOTEDB_H
