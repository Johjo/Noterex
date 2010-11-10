#ifndef DAOFACTORY_H
#define DAOFACTORY_H

#include "notedao.h"

class DAOFactory
{
public:
    DAOFactory() {}

    virtual NoteDAO * getNoteDAO() = 0;
};

#endif // DAOFACTORY_H
