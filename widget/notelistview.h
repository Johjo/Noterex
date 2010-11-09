#ifndef NOTELISTVIEW_H
#define NOTELISTVIEW_H

#include <QListView>

class NoteListView : public QListView
{
    Q_OBJECT
public:
    explicit NoteListView(QObject *parent = 0);

signals:

public slots:

};

#endif // NOTELISTVIEW_H
