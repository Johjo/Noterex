#include "notewidget.h"
#include <QDebug>
#include "model/contentmodel.h"


NoteWidget::NoteWidget(QWidget *parent):
        QWidget(parent)
{
    layout = new QVBoxLayout(this);
    layout->setMargin(0);

    list = new QListView(this);
    text = new QTextEdit(this);
    buttonSave = new QPushButton(tr("note.save"),this);

    layout->addWidget(list);
    layout->addWidget(text);
    layout->addWidget(buttonSave );

    list->setWordWrap(true);
    list->setAlternatingRowColors(true);

    connect(list,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(s_swapToEditMode()));
    connect(buttonSave,SIGNAL(clicked()),this,SLOT(s_saveNotesAndDisplay()));

    s_swapToDisplayMode();
}

void NoteWidget::s_saveNotesAndDisplay() {
    saveNotes();
    s_swapToDisplayMode();
}

void NoteWidget::saveNotes() {
    QString plainTexte = text->toPlainText();
    QStringList list = plainTexte.split(QRegExp("[\r\n]*-{4,}[\r\n]"));
    basket->clearNote();
    basket->addNote(list);
}


void NoteWidget::s_swapToEditMode() {
    list->setVisible(false);
    text->setVisible(true);
    buttonSave->setVisible(true);

    fillText();
}

void NoteWidget::fillText() {
    QString newText;

    for (int i = 0; i < basket->countContent(); i++) {
        newText.append(basket->getContent(i)->getBody());
        newText.append("\n----------\n");
    }

    text->setText(newText);
}


void NoteWidget::s_swapToDisplayMode() {
    list->setVisible(true);
    text->setVisible(false);
    buttonSave->setVisible(false);

    refreshList();
}

void NoteWidget::refreshList() {
    if (basket)
        list->setModel(new ContentModel(basket,list));
}


void NoteWidget::setBasket(QExplicitlySharedDataPointer<Basket> basket) {
    this->basket = basket;

    if (basket) {
        if (basket->countContent() > 0)
            s_swapToDisplayMode();
        else
            s_swapToEditMode();
    }

}


