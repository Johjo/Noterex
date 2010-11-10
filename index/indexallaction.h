#ifndef INDEXALLACTION_H
#define INDEXALLACTION_H


#include <QAction>

#include "note/notedistributor.h"
#include "note/notedao.h"

class IndexAllAction : public QAction
{
    Q_OBJECT
public:
    IndexAllAction(NoteDAO * noteDAO, QObject *parent = 0);
    virtual ~IndexAllAction();

signals:

public slots:
    void IndexAllDocuments();

private:
    NoteDistributor * distributor;

};

#endif // INDEXALLACTION_H
