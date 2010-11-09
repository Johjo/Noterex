#include "createdatabaseaction.h"

#include <QFileDialog>
#include "application.h"
#include "databasecreator.h"
#include "opendatabaseaction.h"

CreateDatabaseAction::CreateDatabaseAction(QObject *parent) :
        QAction(tr("New database"), parent)
{
    connect(this,SIGNAL(triggered()),this, SLOT(chooseFileCreateAndOpenDatabase()));
}

void CreateDatabaseAction::chooseFileCreateAndOpenDatabase() {
    QString filename = chooseFile();

    if (! filename.isEmpty()) {
        DatabaseCreator(filename).create();
        Application::getApplication()->openDatabase(filename);
    }
}


QString CreateDatabaseAction::chooseFile() {
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Database (*.db *.sqlite *.sql)"));
    dialog.setViewMode(QFileDialog::Detail);

    if (dialog.exec()) {
        return dialog.selectedFiles().at(0);
    } else {
        return "";
    }
}

