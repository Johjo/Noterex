#include "notegui.h"

NoteGUI::NoteGUI(Note * note, QObject *parent):
        QObject(parent),
        note(note),
        isUpdated(false)
{}

NoteGUI::~NoteGUI() {
    delete note;
}

QString NoteGUI::getSubject() {
    return note->getSubject();
}

QString NoteGUI::getBody() {
    return note->getBody();
}

QString NoteGUI::getKeywords() {
    return note->getKeywords();
}

void NoteGUI::setSubject(QString subject) {
    note->setSubject(subject);
}

void NoteGUI::setBody(QString body) {
    note->setBody(body);
}

void NoteGUI::setKeywords(QString keywords) {
    note->setKeywords(keywords);
}

bool NoteGUI::isEdited() {
    return isUpdated;
}

void NoteGUI::save() {
    if (isUpdated) {
        note->save();
    }
}

void NoteGUI::remove() {
    note->remove();
}

void NoteGUI::noteChanged() {
    isUpdated = true;
}

NoteGUI::Mode NoteGUI::getMode() {
    return currentMode;
}

void NoteGUI::setMode(NoteGUI::Mode mode) {
    currentMode = mode;
}
