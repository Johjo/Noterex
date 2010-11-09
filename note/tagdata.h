#ifndef TAGDATA_H
#define TAGDATA_H

#include <QString>

class TagData
{
public:
    TagData(QString id = "", QString name = "");

    QString getId();
    QString getName();

    void setName(QString name);

private:
    QString id;
    QString name;
};

#endif // TAGDATA_H
