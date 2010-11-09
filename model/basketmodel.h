#ifndef BASKETMODEL_H
#define BASKETMODEL_H

#include <QAbstractItemModel>
#include <QSqlDatabase>
#include <QModelIndex>
#include <data/basket.h>
#include <QExplicitlySharedDataPointer>

class BasketModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit BasketModel(QObject *parent, QSqlDatabase db);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QExplicitlySharedDataPointer<Basket> getBasket(const QModelIndex &index) const ;

signals:

public slots:

private:
    QSqlDatabase database;

    BasketModel();

};

#endif // BASKETMODEL_H
