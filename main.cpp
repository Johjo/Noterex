#include <QtGui/QApplication>
#include "mainwindow.h"

#include "application.h"

int main(int argc, char *argv[]){
    Application *a = Application::getApplication();
    a->getDatabase();
    return a->run(argc, argv);
}
