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
    if (note == 0) {
        return "";
    } else {
        return note->getSubject();
    }
}

QString NoteGUI::getBody() {
    if (note == 0) {
        return "";
    } else {
        return note->getBody();
    }
}

QString NoteGUI::getKeywords() {
    if (note == 0) {
        return "";
    } else {
        return note->getKeywords();
    }
}

void NoteGUI::setSubject(QString subject) {
    if (note != 0) {
        note->setSubject(subject);
    }
}

void NoteGUI::setBody(QString body) {
    if (note != 0) {
        note->setBody(body);
    }
}

void NoteGUI::setKeywords(QString keywords) {
    if (note != 0) {
        note->setKeywords(keywords);
    }
}

bool NoteGUI::isEdited() {
    return isUpdated;
}

void NoteGUI::save() {
    if (isUpdated && note != 0) {
        note->save();
        isUpdated = false;
    }
}

void NoteGUI::remove() {
    if (note != 0) {
        note->remove();
    }
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
