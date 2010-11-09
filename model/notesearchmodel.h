#ifndef NOTESEARCHMODEL_H
#define NOTESEARCHMODEL_H

#include <QAbstractListModel>

#include "index/searcher.h"

class NoteSearchModel : public QAbstractListModel
{
    Q_OBJECT
public:
    NoteSearchModel(Searcher * searcher, QObject *parent = 0);

    virtual int rowCount(const QModelIndex & parent = QModelIndex() ) const;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole ) const;

signals:

public slots:

private:
    NoteSearchModel(QObject *parent = 0);
    Searcher * searcher;
};

#endif // NOTESEARCHMODEL_H
