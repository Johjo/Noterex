#ifndef TAG_H
#define TAG_H

#include <QString>

class Tag
{
public:
    typedef QList<Tag> List;
    Tag(QString id, int state = 0, QString param = "");

    QString getId();

    void setState(int);
    int getState();

    void setParam(QString);
    QString getParam();

protected:
    Tag();

private:
    QString id;
    int state;
    QString param;

};

#endif // TAG_H
