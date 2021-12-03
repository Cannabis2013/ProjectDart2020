#ifndef DCIPTVALS_H
#define DCIPTVALS_H
#include <QUuid>
struct DCIptVals
{
    int point = 0;
    int score = 0;
    int modKeyCode = -1;
    int remainingScore;
    int min = 0;
    int max = 0;
    double mid = 0;
    int roundIndex = 1;
    int setIndex = 0;
    int attempt = 0;
    bool inGame = false;
    bool approved = false;
    QUuid playerId;
    QString playerName;
};

#endif // DCIPTVALS_H
