#include "formnotecollector.h"
#include "ui_formnotecollector.h"

#include "application.h"
#include "model/noteviewmodel.h"

#include "note/standardnotedistributor.h"



FormNoteCollector::FormNoteCollector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::formNoteCollector),
    noteDAO(Application::getApplication()->getNoteDAO()),
    note(NULL)
{
    createNoteDistributor();

    ui->setupUi(this);
    ui->noteView->setModel(new NoteViewModel(distributor, ui->noteView));

    connect(ui->newButton,SIGNAL(clicked()),this,SLOT(createNote()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeNote()));


    connect(ui->subjectEdit,SIGNAL(editingFinished()),this,SLOT(noteChanged()));
    connect(ui->noteView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(noteSelected(QModelIndex)));
    ui->bodyEdit->installEventFilter(this);
}

FormNoteCollector::~FormNoteCollector()
{
    delete ui;
    delete distributor;
}


void FormNoteCollector::createNoteDistributor() {
    Tag tag("NEW");

    Tag::List tags;
    tags << tag;

    distributor = noteDAO->getNoteDistributor(tags);
}

void FormNoteCollector::createNote() {
    note = noteDAO->create();
    note->setSubject(tr("New note"));

    note->addTag(Tag("NEW"));
    note->save();
}

void FormNoteCollector::removeNote() {
    note->remove();
}

void FormNoteCollector::noteChanged() {
    note->setSubject(ui->subjectEdit->text());
    note->setBody(ui->bodyEdit->toPlainText());
    note->save();
}

bool FormNoteCollector::eventFilter(QObject * object, QEvent * event) {
    if ((object == ui->bodyEdit)) {
        if (event->type() == QEvent::FocusOut) {
            noteChanged();
            return true;
        }
    }

    return false;
}

void FormNoteCollector::noteSelected(QModelIndex index) {
    delete note;
    note = distributor->getNoteFromRow(index.row());

    ui->subjectEdit->setText(note->getSubject());
    ui->bodyEdit->setPlainText(note->getBody());
}
