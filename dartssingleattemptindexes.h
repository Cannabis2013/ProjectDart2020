#ifndef DARTSSINGLEATTEMPTINDEXES_H
#define DARTSSINGLEATTEMPTINDEXES_H

#include "idartssingleattemptindexes.h"
#include "qbytearray.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsPointSingleAttemptContext
{
    class DartsSingleAttemptIndexes :
            public IDartsSingleAttemptIndexes
    {
    public:
        static DartsSingleAttemptIndexes* createInstance()
        {
            return new DartsSingleAttemptIndexes();
        }
        int totalTurns() const override
        {
            return _totalTurns;
        }
        DartsSingleAttemptIndexes* setTotalTurns(const int& totalTurns)
        {
            _totalTurns = totalTurns;
            return this;
        }
        int turnIndex() const override
        {
            return _turnIndex;
        }
        DartsSingleAttemptIndexes* setTurnIndex(const int& turnIndex)
        {
            _turnIndex = turnIndex;
            return this;
        }
        int roundIndex() const override
        {
            return _roundIndex;
        }
        DartsSingleAttemptIndexes* setRoundIndex(const int& roundIndex)
        {
            _roundIndex = roundIndex;
            return this;
        }
        int setIndex() const override
        {
            return _setIndex;
        }
        DartsSingleAttemptIndexes* setSetIndex(const int& setIndex)
        {
            _setIndex = setIndex;
            return this;
        }
        int attemptIndex() const override
        {
            return _attemptIndex;
        }
        DartsSingleAttemptIndexes* setAttemptIndex(const int& attemptIndex)
        {
            _attemptIndex = attemptIndex;
            return this;
        }
    private:
        DartsSingleAttemptIndexes(){}
        int _totalTurns;
        int _turnIndex;
        int _roundIndex;
        int _setIndex;
        int _attemptIndex;
    };
}

#endif // DARTSSINGLEATTEMPTINDEXES_H
