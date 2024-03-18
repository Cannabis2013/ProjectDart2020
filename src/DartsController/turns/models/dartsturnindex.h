#ifndef DARTTURNINDEX_H
#define DARTTURNINDEX_H

#include "dartsindex.h"

class DartsTurnIndex
{
public:
        DartsTurnIndex(const DartsIndex &index){
                _currentTurnIndex = index.currentTurnIndex;
                _currentThrowIndex = index.currentThrowIndex;
                _throwId = index.currentThrows;
                _turnId = index.totalTurns;
        }

        int currentTurnIndex() const
        {
                return _currentTurnIndex;
        }

        int throwIndex() const
        {
                return _currentThrowIndex;
        }

        int throwId() const
        {
                return _throwId;
        }
        
        int turnId() const
        {
                return _turnId;
        }

private:
        int _turnId;
        int _currentTurnIndex;
        int _currentThrowIndex;
        int _throwId;
};

#endif // DARTTURNINDEX_H




