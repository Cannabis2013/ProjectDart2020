#ifndef DCINPUT_H
#define DCINPUT_H

#include <qjsondocument.h>
#include <qjsonobject.h>

struct DCInput
{
    bool approved = false;
    int point = 0;
    int modKeyCode;
    int score = 0;
    int remainingScore = 0;
    QUuid playerId;
    QString playerName;
};
#endif // DARTSPOINT_H
