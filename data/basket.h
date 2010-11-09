#ifndef BASKET_H
#define BASKET_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QSqlDatabase>
#include <QExplicitlySharedDataPointer>
#include <QStringList>

#include "content.h"


class Basket : public QSharedData
{

public:
    enum Mode {NoChange, New, Edited, Deleted};
    Basket();
    explicit Basket(QSqlDatabase);
    Basket(int id, QSqlDatabase);

    virtual int getId();
    virtual int getParentId();
    virtual int getRow();

    virtual bool hasChild(int row);
    virtual bool hasParent();
    virtual bool isRoot();

    virtual QExplicitlySharedDataPointer<Basket> getParent();
    virtual QExplicitlySharedDataPointer<Basket> getChild(int row);

    virtual Mode getCurrentMode();

    virtual int countChild();
    int countContent();
    QExplicitlySharedDataPointer<Content> getContent(int row);

    virtual QString getTitle();

    virtual void setParentId(int id);
    virtual void setTitle(QString title);
    virtual void setRow(int row);

    void clearNote();
    QExplicitlySharedDataPointer<Content> addNote();
    void addNote(QStringList);
    virtual void save();
    void remove();

    static void createTable(QSqlDatabase);

protected:
    QSqlDatabase getDatabase();
    virtual void save(QSqlDatabase);

private:
    QSqlDatabase database;
    int id;
    int row;
    int parentId;
    QString title;
    Mode currentMode;


    void init();
    QList<int> getChildrenId();
};

#endif // BASKET_H
