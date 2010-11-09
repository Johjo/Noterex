#include "basketmodel.h"

#include "data/basket.h"
#include "data/basketroot.h"
#include <QAbstractItemModel>

BasketModel::BasketModel(){}

BasketModel::BasketModel(QObject *parent, QSqlDatabase db) :
        QAbstractItemModel(parent),
        database(db)
{}

QModelIndex BasketModel::index(int row, int column, const QModelIndex &parentIndex) const {
    if (! hasIndex(row, column, parentIndex))
        return QModelIndex();


    QExplicitlySharedDataPointer<Basket> parentBasket = getBasket(parentIndex);
    QExplicitlySharedDataPointer<Basket> childBasket = parentBasket->getChild(row);

    if (childBasket->getCurrentMode() != Basket::New)
        return createIndex(row, column, childBasket->getId());
    else
        return QModelIndex();
}

QExplicitlySharedDataPointer<Basket> BasketModel::getBasket(const QModelIndex &index) const {
    QExplicitlySharedDataPointer<Basket> basket;

    if (!index.isValid()){
        basket = new BasketRoot(database);
    } else {
        basket = new Basket(index.internalId(), database);
    }

    return basket;
}


QModelIndex BasketModel::parent(const QModelIndex &childIndex) const {
    if (!childIndex.isValid())
        return QModelIndex();

    QExplicitlySharedDataPointer<Basket> childBasket = getBasket(childIndex);

    if (! childBasket->hasParent()){
        return QModelIndex();
    }

    QExplicitlySharedDataPointer<Basket> parentBasket = childBasket->getParent();

    return createIndex(parentBasket->getRow(),0,parentBasket->getId());
}

int BasketModel::rowCount(const QModelIndex &index) const{
    if (index.column() > 0)
        return 0;

    return getBasket(index)->countChild() ;
}

int BasketModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

QVariant BasketModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    return Basket(index.internalId(), database).getTitle() + " (" + QString::number(Basket(index.internalId(), database).countContent()) + ")";
}
