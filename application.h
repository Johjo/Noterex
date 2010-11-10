#ifndef APPLICATION_H
#define APPLICATION_H

#include <QSettings>

#include <QSqlDatabase>

#include "note/daofactory.h"
#include "note/notedao.h"

class Application
{
public:
    QSqlDatabase getDatabase();

    virtual ~Application();

    static Application * getApplication();
    int run(int argc, char *argv[]);
    void openDatabase(QString filename);

    DAOFactory * getDAOFactory();
    NoteDAO * getNoteDAO();

private:
    Application();
    static Application * application;
    QSqlDatabase database;
    QSettings settings;
    QString filename;

    void readSettings();
    void openLastDatabaseOrCreateIt();

    DAOFactory * daoFactory;



};

#endif // APPLICATION_H
