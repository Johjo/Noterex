#ifndef CREATEDATABASEACTION_H
#define CREATEDATABASEACTION_H

#include <QAction>

class CreateDatabaseAction : public QAction
{
    Q_OBJECT
public:
    explicit CreateDatabaseAction(QObject *parent = 0);

public slots:
    void chooseFileCreateAndOpenDatabase();


private:
    QString chooseFile();

};

#endif // CREATEDATABASEACTION_H
