#ifndef NOTEVIEWMODEL_H
#define NOTEVIEWMODEL_H

#include <QAbstractListModel>
#include "note/notedistributor.h"

class NoteViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    NoteViewModel(NoteDistributor * distributor, QObject *parent = 0 );
    int rowCount(const QModelIndex & parent = QModelIndex() ) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole ) const;

private:
    NoteViewModel();
    NoteDistributor * distributor;

signals:

public slots:

};

#endif // NOTEVIEWMODEL_H
