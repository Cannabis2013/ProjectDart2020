#ifndef IDARTSSCORE_H
#define IDARTSSCORE_H

#include "quuid.h"
namespace DartsScoreMultiAttemptContext
{
    class IDartsScore
    {
    public:
        virtual int score() const = 0;
        virtual QUuid playerId() const  = 0;
        virtual QString playerName() const = 0;
    };
};

#endif // IDARTSSCORE_H
