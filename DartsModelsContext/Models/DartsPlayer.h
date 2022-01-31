#ifndef DARTSPLAYER_H
#define DARTSPLAYER_H
#include <qstring.h>
#include <quuid.h>
struct DartsPlayer
{
public:
    QString name;
    QUuid id;
};

#endif // DARTSPLAYER_H
