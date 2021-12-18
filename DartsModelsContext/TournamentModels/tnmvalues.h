#ifndef TNMVALUES_H
#define TNMVALUES_H
#include <QString>
#include <QUuid>
struct TnmVals
{
    bool entryRestricted;
    int initRem;
    int playerCount;
    int totalTurns;
    int turnIndex;
    int roundIndex;
    int setIndex;
    int attemptIndex;
    QString winnerName;
    QUuid tournamentId;
};
#endif // TNMVALUES_H
