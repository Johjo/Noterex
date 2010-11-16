#include "notedb.h"

NoteDB::NoteDB(NoteDAO *noteDAO, int id):
        Note(new NoteData()),
        noteDAO(noteDAO),
        id(id)
{}

NoteDB::NoteDB(NoteData *data, NoteDAO *noteDAO, int id):
        Note(data),
        noteDAO(noteDAO),
        id(id)
{}

NoteDB::~NoteDB() {
}

void NoteDB::save() {
    noteDAO->save(this);
}

void NoteDB::remove() {
    noteDAO->remove(this);
}

int NoteDB::getId(){
    return id;
}

void NoteDB::setId(int id){
    this->id = id;
}

