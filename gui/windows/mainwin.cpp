#include "mainwin.h"
#include "ui_mainwin.h"

#include <QBoxLayout>

#include "gui/widget/formnotecollector.h"

MainWin::MainWin(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWin)
{
    ui->setupUi(this);

    QLayout *layout = ui->centralwidget->layout();
    layout->addWidget(new FormNoteCollector(this));
}

MainWin::~MainWin()
{
    delete ui;
}
