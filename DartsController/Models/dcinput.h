#ifndef DCINPUT_H
#define DCINPUT_H
#include <QUuid>
struct DCInput
{
    int point = 0;
    int score = 0;
    int modKeyCode = -1;
    int remScore = -1;
    int min = 0;
    int max = 0;
    double mid = 0;
    int roundIndex = 1;
    int playerIndex = 0;
    int attemptIndex = 0;
    bool inGame = false;
    bool approved = false;
    QUuid tournamentId;
    QString playerName;
    QUuid playerId;
};

#endif // DCINPUT_H
