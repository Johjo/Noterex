#ifndef NOTEGUI_H
#define NOTEGUI_H

#include <QObject>

#include "note.h"

class NoteGUI : public QObject
{
    Q_OBJECT
public:
    enum Mode {DISPLAY, EDIT};

    NoteGUI(Note* note = 0 ,QObject *parent = 0);
    ~NoteGUI();

    QString getSubject();
    QString getBody();
    QString getKeywords();

    void setSubject(QString subject);
    void setBody(QString body);
    void setKeywords(QString keywords);

    bool isEdited();

    Mode getMode();
    void setMode(Mode);

private:
    Note * note;
    bool isUpdated;

    Mode currentMode;

public slots:
    void noteChanged();
    void save();
    void remove();
};

#endif // NOTEGUI_H
