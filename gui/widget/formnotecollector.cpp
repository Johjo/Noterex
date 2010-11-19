#include "formnotecollector.h"
#include "ui_formnotecollector.h"

#include "application.h"
#include "model/noteviewmodel.h"

#include "note/standardnotedistributor.h"
#include "note/note.h"


FormNoteCollector::FormNoteCollector(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::formNoteCollector),
        noteDAO(Application::getApplication()->getNoteDAO()),
        noteGui(new NoteGUI())
{
    createNoteDistributor();

    ui->setupUi(this);
    ui->noteView->setModel(new NoteViewModel(distributor, ui->noteView));

    connect(ui->newButton,SIGNAL(clicked()),this,SLOT(slotCreateNote()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeNote()));

    connect(ui->noteView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(slotNoteSelected(QModelIndex)));
    connect(ui->bodyEdit,SIGNAL(textChanged()),this,SLOT(slotBodyChanged()));

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

void FormNoteCollector::slotCreateNote(){
    noteGui->save();

    createNoteGui(createNote());

    ui->subjectEdit->setFocus(Qt::OtherFocusReason);
    ui->subjectEdit->selectAll();
}

void FormNoteCollector::createNoteGui(Note *note) {
    delete noteGui;
    noteGui = new NoteGUI(note,this);

    ui->subjectEdit->setText(noteGui->getSubject());
    ui->bodyEdit->setPlainText(noteGui->getSubject());

    connect(ui->subjectEdit,SIGNAL(textEdited(QString)),noteGui,SLOT(noteChanged()));
    connect(ui->bodyEdit,SIGNAL(textChanged()),noteGui,SLOT(noteChanged()));

    connect(ui->subjectEdit,SIGNAL(textChanged(QString)),noteGui,SLOT(setSubject(QString)));

    connect(ui->subjectEdit,SIGNAL(editingFinished()),noteGui,SLOT(save()));
    connect(ui->subjectEdit,SIGNAL(editingFinished()),noteGui,SLOT(save()));
}

Note * FormNoteCollector::createNote() {
    Note * note = noteDAO->create();
    note->setSubject(tr("New note"));
    note->addTag(Tag("NEW"));

    return note;
}

void FormNoteCollector::removeNote() {
    distributor->getNoteFromRow(ui->noteView->selectionModel()->currentIndex().row())->remove();
}

bool FormNoteCollector::eventFilter(QObject * object, QEvent * event) {
    if ((object == ui->bodyEdit)) {
        if (event->type() == QEvent::FocusOut) {
            noteGui->save();
            return true;
        }
    }
    return false;
}

void FormNoteCollector::slotNoteSelected(QModelIndex index) {
    createNoteGui(distributor->getNoteFromRow(index.row()));

    ui->subjectEdit->setText(noteGui->getSubject());
    ui->bodyEdit->setPlainText(noteGui->getBody());
}

void FormNoteCollector::slotBodyChanged() {
    noteGui->setBody(ui->bodyEdit->toPlainText());
}
