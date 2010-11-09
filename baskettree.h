#ifndef BASKETTREE_H
#define BASKETTREE_H

#include <QTreeView>
#include <QSqlDatabase>
#include <QExplicitlySharedDataPointer>
#include <data/basket.h>

class BasketTree : public QTreeView
{
    Q_OBJECT
public:
    explicit BasketTree(QWidget * parent = 0);
    void setDatabase(QSqlDatabase);
    int getCurrentId();
    QExplicitlySharedDataPointer<Basket> getCurrentBasket() ;

signals:
    void addBasket();
    void removeBasket();

public slots:
    void s_contextMenu(const QPoint&);
    void s_addBasket();
    void s_removeBasket();

private:
    QSqlDatabase database;

};

#endif // BASKETTREE_H
