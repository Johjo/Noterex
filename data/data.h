#ifndef DATA_H
#define DATA_H

#include <QDebug>

#include <QSqlDatabase>
#include <QSharedData>

class Data: public QSharedData
{
public:
    Data():id(-1),currentMode(New){}
    Data(int id):id(id){}

    enum Mode {New, Existing, Deleted};

    Mode getCurrentMode() {return currentMode;}
    int getId() {return this->id;}

    bool canBeInserted() {return (currentMode == New && isEdited()) || currentMode == Deleted;}
    bool canBeUpdated() {return isEdited();}
    bool canBeDeleted() {return currentMode == Existing;}

    virtual void save() {v_save();}
    virtual void remove() {v_remove();}
    virtual bool isEdited() {return edited;}
    virtual void setEdited(bool edited) {this->edited = edited;}

protected:
    void setCurrendMode(Mode mode) {this->currentMode = mode;}
    void setId(int id){this->id = id;}

    virtual void v_save()=0;
    virtual void v_remove()=0;

protected :int id;
private: Mode currentMode;
private: bool edited;




};

#endif // DATA_H
