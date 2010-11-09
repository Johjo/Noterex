#include "opendatabaseaction.h"

#include <QFileDialog>

#include "application.h"

OpenDatabaseAction::OpenDatabaseAction(QObject *parent) :
    QAction(tr("Open database"), parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(chooseFileAndOpenDatabase()));
}

void OpenDatabaseAction::chooseFileAndOpenDatabase() {
    QString filename = chooseFile();

    openDataBase(filename);
}

QString OpenDatabaseAction::chooseFile() {
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Database (*.db *.sqlite *.sql)"));
    dialog.setViewMode(QFileDialog::Detail);

    if (dialog.exec()) {
        return dialog.selectedFiles().at(0);
    } else {
        return "";
    }
}

void OpenDatabaseAction::openDataBase(QString filename){
    Application::getApplication()->openDatabase(filename);
}
