#ifndef TNMVALUES_H
#define TNMVALUES_H
#include <QString>
#include <QUuid>
struct TnmVals
{
    bool entryRestricted;
    int initRem;
    int playerCount;
    QString winnerName;
    QUuid tournamentId;
    int totalTurns;
    int turnIndex;
    int roundIndex;
    int setIndex;
    int attemptIndex;
};
#endif // TNMVALUES_H
