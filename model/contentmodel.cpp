#include "contentmodel.h"

ContentModel::ContentModel()
{}

ContentModel::ContentModel(QExplicitlySharedDataPointer<Basket> parentBasket, QObject *parent):
    QAbstractListModel(parent),
    parentBasket(parentBasket)
{

}


int ContentModel::rowCount(const QModelIndex & parent) const {
    return parentBasket->countContent();
}

QVariant ContentModel::data(const QModelIndex & index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    return parentBasket->getContent(index.row())->getBody();
}
