#ifndef DARTTURNINDEX_H
#define DARTTURNINDEX_H

#include "dartsindex.h"

class DartsTurnIndex
{
public:
        DartsTurnIndex(const DartsIndex &index){
                _playerIndex = index.playerIndex;
                _legIndex = index.legIndex;
                _turnIndex = index.turnIndex;
        }

        int playerIndex() const
        {
                return _playerIndex;
        }

        int legIndex() const
        {
                return _legIndex;
        }

        int turnIndex() const
        {
                return _turnIndex;
        }

private:
        int _playerIndex;
        int _legIndex;
        int _turnIndex;
};

#endif // DARTTURNINDEX_H




