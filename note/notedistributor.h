#ifndef NOTEDISTRIBUTOR_H
#define NOTEDISTRIBUTOR_H

#include "notedb.h"

class NoteDistributor {

public:
    NoteDistributor() {}
    virtual ~NoteDistributor() {}

    virtual int count() const = 0;
    virtual NoteDB * getNoteFromRow(int row) = 0;

    virtual void refresh() = 0;
};


#endif // NOTEDISTRIBUTOR_H
