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
    int remainingScoreCand = 0;
    double middle = 0;
    bool inGame = false;
    int min = 0;
    int max = 0;
    QUuid playerId;
    QString playerName;
};
#endif // DARTSPOINT_H
