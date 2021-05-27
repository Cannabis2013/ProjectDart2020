#ifndef DARTSPOINTMODELS_H
#define DARTSPOINTMODELS_H

#include <quuid.h>

namespace DartsPointInputContext {
    struct DartsInputKeyValues
    {
        int pointValue;
        int modKeyCode;
    };
    struct DartsPointModel
    {
        int pointValue;
        int modKeyCode;
        int score;
        QUuid playerId;
    };
    struct DartsSingleAttemptIndexes
    {
        int totalTurns;
        int turns;
        int roundIndex;
        int setIndex;
        int attemptIndex;
    };
}

#endif // DARTSPOINTMODELS_H
