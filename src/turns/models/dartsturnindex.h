#ifndef DARTTURNINDEX_H
#define DARTTURNINDEX_H

#include "dartsindex.h"

class DartsTurnIndex
{
public:
        DartsTurnIndex(const DartsIndex &index){
                _turnIndex = index.turnIndex;
                _roundIndex = index.roundIndex;
                _turnId = index.turnCount;
        }

        int turnIndex() const
        {
                return _turnIndex;
        }

        int roundIndex() const
        {
                return _roundIndex;
        }
        
        int turnId() const
        {
                return _turnId;
        }

private:
        int _turnIndex;
        int _turnId;
        int _roundIndex;
};
#endif // DARTTURNINDEX_H
