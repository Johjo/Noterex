#ifndef CONTENT_H
#define CONTENT_H

#include <QString>
#include <QVariant>
#include <QSqlDatabase>
#include <QSharedData>

class Content : public QObject, public QSharedData
{
    Q_OBJECT

public:
    enum Mode {NoChange, New, Edited, Deleted};
    explicit Content(QSqlDatabase);
    Content(int id, QSqlDatabase);

    int getId() const;
    int getBasketId() const;
    void setBasketId(int);
    int getRow() const;
    int getColumn() const;
    QString getBody() const;
    Mode getCurrentMode() const;

    bool operator ==(const Content &n);
    void save(QSqlDatabase);

    static void createTable(QSqlDatabase);

public slots:
    void remove();
    void setRow(int);
    void setcolumn(int);
    void setBody(QString);
    void save();

protected:
    int id;
    QString body;

private:
    Mode currentMode;
    int row, column;
    int basketId;
    QSqlDatabase database;

    Content();
    void setId(int);

};

#endif // NOTE_H
