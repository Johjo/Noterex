#ifndef OPENDATABASEACTION_H
#define OPENDATABASEACTION_H

#include <QAction>

class OpenDatabaseAction : public QAction
{
    Q_OBJECT
public:
    explicit OpenDatabaseAction(QObject *parent = 0);  
    void openDataBase(QString filename);

signals:

public slots:
    void chooseFileAndOpenDatabase();

private:
    QString chooseFile();


};

#endif // OPENDATABASEACTION_H
