#ifndef TABLE_H
#define TABLE_H

#include <QSqlDatabase>
#include <QSharedData>


class Table : public QSharedData
{
public:
    Table(QSqlDatabase db):database(db) {}

    QSqlDatabase getDatabase() {return database;}

    virtual void refresh() = 0;

protected:
    Table(){}

private:
    QSqlDatabase database;
};

#endif // TABLE_H
