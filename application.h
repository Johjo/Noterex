#ifndef APPLICATION_H
#define APPLICATION_H

#include <QSettings>

#include <QSqlDatabase>

class Application
{
public:
    QSqlDatabase getDatabase();

    virtual ~Application();

    static Application * getApplication();
    int run(int argc, char *argv[]);
    void openDatabase(QString filename);

private:
    Application();
    static Application * application;
    QSqlDatabase database;
    QSettings settings;
    QString filename;

    void readSettings();
    void openLastDatabaseOrCreateIt();

};

#endif // APPLICATION_H
