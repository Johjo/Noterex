#include "baskettree.h"

#include <QMenu>
#include "data/basket.h"

BasketTree::BasketTree(QWidget *parent) :
    QTreeView(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(s_contextMenu(const QPoint&)));
    connect(this,SIGNAL(addBasket()),this,SLOT(s_addBasket()));
    connect(this,SIGNAL(removeBasket()),this,SLOT(s_removeBasket()));
}

void BasketTree::setDatabase(QSqlDatabase database){
    this->database = database;
}

void BasketTree::s_contextMenu(const QPoint &pos) {
    QMenu * menu = new QMenu(this);
    menu->addAction(tr("basket.add"),this,SIGNAL(addBasket()));
    menu->addAction(tr("basket.remove"),this,SIGNAL(removeBasket()));
    menu->exec(mapToGlobal(pos));
}

void BasketTree::s_addBasket() {
    QModelIndex index = selectionModel()->currentIndex();

    Basket basket(database);
    basket.setTitle("new");
    basket.setParentId(index.internalId());
    basket.save();

    emit rowsInserted(index, index.row(), index.row());

}

void BasketTree::s_removeBasket() {
    QModelIndex index = selectionModel()->currentIndex();

    getCurrentBasket()->remove();
    emit rowsRemoved(index.parent(),index.row(),index.row());

}


int BasketTree::getCurrentId() {
    return selectionModel()->currentIndex().internalId();
}

QExplicitlySharedDataPointer<Basket> BasketTree::getCurrentBasket() {
    QExplicitlySharedDataPointer<Basket> basket ;
    basket = new Basket(getCurrentId(),database);

    return basket;
}


