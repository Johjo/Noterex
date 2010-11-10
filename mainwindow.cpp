#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QDebug>
#include <QMenuBar>

#include "database/opendatabaseaction.h"
#include "database/createdatabaseaction.h"

#include "model/noteviewmodel.h"
#include "application.h"

#include "note/standardnotedistributor.h"
#include "note/searchnotedistributor.h"

#include "index/indexallaction.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        currentNote(0),
        noteDAO(Application::getApplication()->getNoteDAO()),
        notes()
{
    ui->setupUi(this);
    s_updateSearch();
    connectSignals();
    createMenu();
    createEmptyNote();
}

void MainWindow::connectSignals() {
    connect(ui->newNoteButton,SIGNAL(clicked()),this,SLOT(s_createNote()));
    connect(ui->deleteNoteButton,SIGNAL(clicked()),this,SLOT(s_removeNote()));
    connect(ui->saveNoteButton,SIGNAL(clicked()),this,SLOT(s_saveNote()));
    connect(ui->editNoteButton,SIGNAL(clicked()),this,SLOT(s_editNote()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(s_cancelNote()));

    connect(ui->noteSearchEdit, SIGNAL(editingFinished()),this,SLOT(s_updateSearch()));

    connect(ui->tabNotes,SIGNAL(currentChanged(int)),this,SLOT(s_changeTab(int)));
    connect(ui->tabNotes,SIGNAL(tabCloseRequested(int)), this, SLOT(s_closeTab(int)));

    connect(ui->noteView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(s_selectNote(QModelIndex)));
}

void MainWindow::createMenu() {
    QMenu * menuFiles = this->menuBar()->addMenu(tr("Files"));
    menuFiles->addAction(new CreateDatabaseAction(this));
    menuFiles->addAction(new OpenDatabaseAction(this));

    QMenu * menuTools = this->menuBar()->addMenu(tr("Tools"));
    menuTools ->addAction(new IndexAllAction(noteDAO, this));
}

MainWindow::~MainWindow(){
    delete ui;
    delete distributor;
}

void MainWindow::s_selectNote(QModelIndex index){
    NoteGUI * note = new NoteGUI(distributor->getNoteFromRow(index.row()), this);
    addNote(note);
}

void MainWindow::addNote(NoteGUI * note) {
    connect(ui->noteSubject,SIGNAL(textChanged(QString)), note,SLOT(noteChanged()));
    connect(ui->noteBody,SIGNAL(textChanged()), note,SLOT(noteChanged()));

    notes.append(note);
    ui->tabNotes->addTab(new QWidget(), note->getSubject());
    ui->tabNotes->setCurrentIndex(notes.count() - 1);
}

void MainWindow::closeEvent(QCloseEvent * e) {
    if (notes.count() > 0) {
        int i = 0;

        while (i < notes.count() && notes[i]->getMode() != NoteGUI::EDIT) {
            i ++;
        }

        if (i < notes.count()) {
            e->ignore();
        }
    }
}

void MainWindow::s_updateSearch() {
    distributor = getDistributor(ui->noteSearchEdit->text());

    noteModel = new NoteViewModel(distributor,ui->noteView);
    ui->noteView->setModel(noteModel); 
}

NoteDistributor * MainWindow::getDistributor(QString searchedText) {
    if (searchedText.trimmed().isEmpty()) {
        return noteDAO->getNoteDistributor();
    } else {
        return noteDAO->getNoteDistributor((searchedText.trimmed()));
    }
}

void MainWindow::s_refreshNote() {
    currentNote = notes[ui->tabNotes->currentIndex()];

    ui->noteSubject->setText(currentNote->getSubject());
    ui->noteBody->setPlainText(currentNote->getBody());
}

void MainWindow::s_createNote() {
    NoteGUI * note = new NoteGUI(noteDAO->create(), this);

    note->setMode(NoteGUI::EDIT);
    addNote(note);
}

void MainWindow::s_editNote() {
    currentNote->setMode(NoteGUI::EDIT);
    updateMode();
}

void MainWindow::s_removeNote() {
    NoteGUI * note = new NoteGUI(distributor->getNoteFromRow(ui->noteView->currentIndex().row()), this);
    note->remove();
    delete note;
    distributor->refresh();
}

void MainWindow::s_saveNote() {
    currentNote->setSubject(ui->noteSubject->text());
    currentNote->setBody(ui->noteBody->toPlainText());
    currentNote->save();
    distributor->refresh(); 
    ui->tabNotes->setTabText(ui->tabNotes->currentIndex(), currentNote->getSubject());
    currentNote->setMode(NoteGUI::DISPLAY);
    updateMode();
}

void MainWindow::s_cancelNote() {
    s_refreshNote();
    currentNote->setMode(NoteGUI::DISPLAY);
    updateMode();
}

void MainWindow::s_changeTab(int i) {
    setCurrentNote(notes[i]);
}

void MainWindow::setCurrentNote(NoteGUI * note){
    currentNote = note;
    updateMode();
    s_refreshNote();
}

void MainWindow::updateMode() {
    if (currentNote->getMode() == NoteGUI::EDIT) {
        setEditMode();
    } else {
        setDisplayMode();
    }
}

void MainWindow::setEditMode() {
    ui->editNoteButton->hide();

    ui->saveNoteButton->show();
    ui->cancelButton->show();

    ui->noteSubject->setReadOnly(false);
    ui->noteBody->setReadOnly(false);
}

void MainWindow::setDisplayMode() {
    ui->editNoteButton->show();

    ui->saveNoteButton->hide();
    ui->cancelButton->hide();

    ui->noteSubject->setReadOnly(true);
    ui->noteBody->setReadOnly(true);
}

void MainWindow::s_closeTab(int i) {
    if (ui->tabNotes->count() == 1 && notes.at(0)->getMode() != NoteGUI::EDIT) {
        createEmptyNote();
    }
    closeTabIfNotEditMode(i);

    s_changeTab(ui->tabNotes->currentIndex());
}

void MainWindow::closeTabIfNotEditMode(int i) {
    if (notes.at(i)->getMode() != NoteGUI::EDIT) {
        ui->tabNotes->removeTab(i);
        delete notes.takeAt(i);
    }
}

void MainWindow::createEmptyNote() {
    NoteGUI * note = new NoteGUI(noteDAO->create(), this);

    note->setMode(NoteGUI::DISPLAY);

    addNote(note);
}
