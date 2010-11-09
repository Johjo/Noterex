#ifndef CONTENTMODEL_H
#define CONTENTMODEL_H

#include <QAbstractListModel>
#include <QExplicitlySharedDataPointer>
#include "data/basket.h"


class ContentModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ContentModel(QExplicitlySharedDataPointer<Basket> parentBasket, QObject *parent = 0);
    int rowCount(const QModelIndex & parent = QModelIndex() ) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole ) const;

private:
    ContentModel();
    QExplicitlySharedDataPointer<Basket> parentBasket;

signals:

public slots:



};

#endif // CONTENTMODEL_H
