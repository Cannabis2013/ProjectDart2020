#ifndef DARTSSCOREMODELS_H
#define DARTSSCOREMODELS_H

#include <quuid.h>

namespace DartsScoresContext {
    struct DartsInputKeyValues
    {
        int score;
    };
    struct DartsScore
    {
        int score;
        QUuid playerId;
        QString playerName;
    };
    struct DartsInputPlayerDetails
    {
        QUuid playerId;
        QString playerName;
    };
    struct DartsSingleAttemptIndexes
    {
        int totalTurns;
        int turns;
        int roundIndex;
        int setIndex;
    };
}

#endif // DARTSSCOREMODELS_H
