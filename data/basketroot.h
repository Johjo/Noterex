#ifndef BASKETROOT_H
#define BASKETROOT_H

#include "basket.h"

#include <QSqlDatabase>

class BasketRoot : public Basket
{
public:
    BasketRoot(QSqlDatabase);

    virtual int getId();
    virtual int getParentId();
    virtual int getRow();

    virtual bool hasChild(int row);
    virtual bool hasParent();

    virtual QExplicitlySharedDataPointer<Basket> getParent();
    virtual QExplicitlySharedDataPointer<Basket> getChild(int row);

    virtual Mode getCurrentMode();

    virtual int countChild();

    virtual QString getTitle();

    virtual void setParentId(int id);
    virtual void setTitle(QString title);
    virtual void setRow(int row);

    virtual void save(QSqlDatabase);
    virtual void save();

protected :
    void init();

private:
    QList<int> childrenId;
    void initChildren();

};

#endif // BASKETROOT_H
