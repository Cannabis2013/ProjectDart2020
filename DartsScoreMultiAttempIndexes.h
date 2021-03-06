#ifndef DARTSSCOREMULTIATTEMPINDEXES_H
#define DARTSSCOREMULTIATTEMPINDEXES_H

#include "idartsmultiattemptindexes.h"

namespace DartsScoreMultiAttemptContext {
    class DartsMultiAttemptIndexes : public
            IDartsMultiAttemptIndexes
    {
    public:
        int totalTurns() const override
        {
            return _totalTurns;
        }
        int turns() const override
        {
            return _turns;
        }
        int roundIndex() const override
        {
            return _roundIndex;
        }
        int setIndex() const override
        {
            return _setIndex;
        }
        void setTotalTurns(int newTotalTurns)
        {
            _totalTurns = newTotalTurns;
        }

        void setTurns(int newTurns)
        {
            _turns = newTurns;
        }

        void setRoundIndex(int newRoundIndex)
        {
            _roundIndex = newRoundIndex;
        }

        void setSetIndex(int newSetIndex)
        {
            _setIndex = newSetIndex;
        }

    private:
        int _totalTurns;
        int _turns;
        int _roundIndex;
        int _setIndex;
    };
}

#endif // DARTSSCOREMULTIATTEMPINDEXES_H
