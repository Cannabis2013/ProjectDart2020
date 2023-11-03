#ifndef DARTTURNINDEX_H
#define DARTTURNINDEX_H

#include "dartsindex.h"

class DartsTurnIndex
{
public:
        DartsTurnIndex(const DartsIndex &index){
                _playerIndex = index.playerIndex;
                _turnIndex = index.turnIndex;
                _throwIndex = index.throwIndex;
        }

        int playerIndex() const
        {
                return _playerIndex;
        }

        int turnIndex() const
        {
                return _turnIndex;
        }

        int throwIndex() const
        {
                return _throwIndex;
        }

private:
        int _playerIndex;
        int _turnIndex;
        int _throwIndex;
};

#endif // DARTTURNINDEX_H




