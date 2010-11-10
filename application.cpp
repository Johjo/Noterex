#include "application.h"

#include <QApplication>

#include "database/createdatabaseaction.h"

#include "mainwindow.h"
#include "note/daofactorysql.h"


Application * Application::application = NULL;

Application::Application():
        database(QSqlDatabase::addDatabase("QSQLITE", "noterex")),
        settings("./noterex.ini",QSettings::IniFormat)
{
}

Application::~Application() {
    database.close();
    QSqlDatabase::removeDatabase("noterex");
}

int Application::run(int argc, char *argv[]) {
    QApplication a(argc, argv);

    readSettings();
    openLastDatabaseOrCreateIt();


    MainWindow w;
    w.show();

    return a.exec();
}

void Application::openDatabase(QString filename) {
    if (database.isOpen()) {
        database.close();
    }

    database.setDatabaseName(filename);
    database.open();

    settings.setValue("filename",filename);

    daoFactory = new DAOFactorySql(database);
}

Application * Application::getApplication() {
    if (application == NULL) {
        application = new Application();
    }

    return application;
}

QSqlDatabase Application::getDatabase() {
    return database;
}

void Application::readSettings() {
    filename = settings.value("filename").toString();
}

void Application::openLastDatabaseOrCreateIt() {
    if (filename.isEmpty()) {
        CreateDatabaseAction action;
        action.chooseFileCreateAndOpenDatabase();
    } else {
        openDatabase(filename);
    }
}

DAOFactory* Application::getDAOFactory() {
    return daoFactory;
}

NoteDAO* Application::getNoteDAO() {
    return daoFactory->getNoteDAO();
}
