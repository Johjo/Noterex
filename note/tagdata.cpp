#include "tagdata.h"

TagData::TagData(QString id, QString name):
        id(id),
        name(name)
{
}

QString TagData::getId() {
    return id;
}

QString TagData::getName() {
    return name;
}

void TagData::setName(QString name) {
    this->name = name;
}
