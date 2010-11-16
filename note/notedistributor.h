#ifndef NOTEDISTRIBUTOR_H
#define NOTEDISTRIBUTOR_H

#include <QObject>

#include "note.h"

class NoteDistributor : public QObject
{
    Q_OBJECT

public:
    NoteDistributor():QObject(0) {}
    virtual ~NoteDistributor() {}

    virtual int count() const = 0;
    virtual Note * getNoteFromRow(int row) = 0;


public slots:
    virtual void refresh() = 0;

signals:
    void dataChanged();

};


#endif // NOTEDISTRIBUTOR_H
