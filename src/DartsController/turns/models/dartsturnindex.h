#ifndef DARTTURNINDEX_H
#define DARTTURNINDEX_H

#include "dartsindex.h"

class DartsTurnIndex
{
public:
        DartsTurnIndex(const DartsIndex &index){
                _turnIndex = index.turnIndex;
                _throwId = index.throwCount;
                _throwIndex = index.throwIndex;
                _roundIndex = index.roundIndex;
                _totalTurns = index.turnId;
        }

        int turnIndex() const
        {
                return _turnIndex;
        }

        int throwIndex() const
        {
                return _throwIndex;
        }

        int roundIndex() const
        {
                return _roundIndex;
        }
        
        int turnId() const
        {
                return _totalTurns;
        }
        
        int throwId() const
        {
                return _throwId;
        }

private:
        int _turnIndex;
        int _totalTurns;
        int _throwId;
        int _throwIndex;
        int _roundIndex;
};
#endif // DARTTURNINDEX_H
