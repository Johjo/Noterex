#include "basketroot.h"

#include <QSqlQuery>

BasketRoot::BasketRoot(QSqlDatabase database):
        Basket(0, database)
{
    initChildren();
}

void BasketRoot::init() {
    initChildren();
}

void BasketRoot::initChildren() {
    QSqlQuery query("SELECT id, row FROM basket WHERE parentId not in (select id from basket) order by row", getDatabase());

    while(query.next()) {
        childrenId << query.value(0).toInt();
    }
}

int BasketRoot::getId() {return 0;}
int BasketRoot::getParentId() {return 0;}
int BasketRoot::getRow(){return 0;}

bool BasketRoot::hasChild(int row){
    return childrenId.count() > row ;
}

bool BasketRoot::hasParent(){return false;}

QExplicitlySharedDataPointer<Basket> BasketRoot::getParent(){
    QExplicitlySharedDataPointer<Basket> root ;
    root = new BasketRoot(getDatabase());
    return root;
}

QExplicitlySharedDataPointer<Basket> BasketRoot::getChild(int row){
    QExplicitlySharedDataPointer<Basket> child;
    child = new Basket(childrenId.value(row,-1),getDatabase());
    return child;
}

Basket::Mode BasketRoot::getCurrentMode(){
    return NoChange;
}

int BasketRoot::countChild(){
    return childrenId.count();
}

QString BasketRoot::getTitle(){
    return QObject::tr("basket.root");
}

void BasketRoot::setParentId(int){}
void BasketRoot::setTitle(QString){}
void BasketRoot::setRow(int){}

void BasketRoot::save(QSqlDatabase){


}
void BasketRoot::save(){


}


