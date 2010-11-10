#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QModelIndex>

#include "model/noteviewmodel.h"

#include "note/notegui.h"
#include "note/notedistributor.h"
#include "note/notedao.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void s_selectNote(QModelIndex);
    void s_createNote();
    void s_updateSearch();

    void s_editNote();
    void s_removeNote();
    void s_saveNote();
    void s_cancelNote();

    void s_refreshNote();
    void s_changeTab(int);
    void s_closeTab(int);

private:
    Ui::MainWindow *ui;
    NoteGUI * currentNote;
    QAbstractItemModel * noteModel;

    NoteDAO * noteDAO;
    NoteDistributor * distributor;
    QList<NoteGUI *> notes;

    void closeEvent(QCloseEvent *);

    void setDisplayMode();
    void setEditMode();

    NoteDistributor * getDistributor(QString searchedText);

    void setCurrentNote(NoteGUI *);
    void updateMode();
    void addNote(NoteGUI *);

    void connectSignals();
    void createMenu();

    void closeTabIfNotEditMode(int i);
    void createEmptyNote();
};

#endif // MAINWINDOW_H
