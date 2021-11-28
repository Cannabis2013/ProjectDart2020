#ifndef DCIPTVALS_H
#define DCIPTVALS_H
#include <QUuid>
struct DCIptVals
{
    int point = 0;
    int score = 0;
    int modKeyCode;
    int remainingScore;
    int min;
    int max;
    double mid;
    int roundIndex;
    int setIndex;
    int attempt;
    bool inGame = false;
    bool approved = false;
    QUuid playerId;
    QString playerName;
};

#endif // DCIPTVALS_H
