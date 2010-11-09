#ifndef INDEXALLACTION_H
#define INDEXALLACTION_H

#include "note/notedistributor.h"

#include <QAction>

class IndexAllAction : public QAction
{
    Q_OBJECT
public:
    explicit IndexAllAction(QObject *parent = 0);
    virtual ~IndexAllAction();

signals:

public slots:
    void IndexAllDocuments();

private:
    NoteDistributor * distributor;

};

#endif // INDEXALLACTION_H
