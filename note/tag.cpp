#include "tag.h"

Tag::Tag()
{
}

Tag::Tag(QString id, int state, QString param):
        id(id),
        state(state),
        param(param)

{}


QString Tag::getId() {
    return id;
}

void Tag::setState(int state){
    this->state = state;
}

int Tag::getState() {
    return state;
}

void Tag::setParam(QString param){
    this->param = param;
}

QString Tag::getParam() {
    return param;
}

