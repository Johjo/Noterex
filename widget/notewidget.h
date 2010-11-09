#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QListView>
#include <QTextEdit>
#include <QPushButton>

#include "data/basket.h"

class NoteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NoteWidget(QWidget *parent = 0);
    void setBasket(QExplicitlySharedDataPointer<Basket> basket);

protected:
    void fillText();
    void saveNotes();
    void refreshList();
private:
    QVBoxLayout * layout;
    QListView* list;
    QTextEdit * text;
    QPushButton * buttonSave;
    QExplicitlySharedDataPointer<Basket> basket;

signals:

public slots:
    void s_saveNotesAndDisplay();
    void s_swapToEditMode();
    void s_swapToDisplayMode();



};

#endif // NOTEWIDGET_H
