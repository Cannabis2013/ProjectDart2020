#ifndef DCINPUT_H
#define DCINPUT_H
#include "dcindex.h"
#include <QUuid>
struct DCInput
{
    int point = 0;
    int score = 0;
    int modKeyCode = -1;
    int remScore = -1;
    bool inGame = false;
    bool approved = false;
    DCIndex index;
    QUuid tournamentId;
    QString playerName;
    QUuid playerId;
};

#endif // DCINPUT_H
