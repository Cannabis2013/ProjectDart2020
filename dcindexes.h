#ifndef DCINDEXES_H
#define DCINDEXES_H

#include <idcindexes.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DCContext
{
    class DCIndexes : public DCContext::IDCIndexes
    {
    public:
        static DCIndexes* createInstance()
        {
            return new DCIndexes();
        }
        int totalTurns() const override
        {
            return _totalTurns;
        }
        DCIndexes* setTotalTurns(const int& totalTurns)
        {
            _totalTurns = totalTurns;
            return this;
        }
        int turnIndex() const override
        {
            return _turnIndex;
        }
        DCIndexes* setTurnIndex(const int& turnIndex)
        {
            _turnIndex = turnIndex;
            return this;
        }
        int roundIndex() const override
        {
            return _roundIndex;
        }
        DCIndexes* setRoundIndex(const int& roundIndex)
        {
            _roundIndex = roundIndex;
            return this;
        }
        int setIndex() const override
        {
            return _setIndex;
        }
        DCIndexes* setSetIndex(const int& setIndex)
        {
            _setIndex = setIndex;
            return this;
        }
        int attemptIndex() const override
        {
            return _attemptIndex;
        }
        DCIndexes* setAttemptIndex(const int& attemptIndex)
        {
            _attemptIndex = attemptIndex;
            return this;
        }
    private:
        DCIndexes(){}
        int _totalTurns;
        int _turnIndex;
        int _roundIndex;
        int _setIndex;
        int _attemptIndex;
    };
}
#endif // DARTSSINGLEATTEMPTINDEXES_H
