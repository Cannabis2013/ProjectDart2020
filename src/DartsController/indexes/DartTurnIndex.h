#ifndef DARTTURNINDEX_H
#define DARTTURNINDEX_H

#include "dartsindex.h"

class DartTurnIndex
{
public:
    static DartTurnIndex fromIndex(DartsIndex index){
                DartTurnIndex turnIndex;
                turnIndex._playerIndex = index.playerIndex;
                turnIndex._legIndex = index.legIndex;
                return turnIndex;
        }


        int playerIndex() const
        {
                return _playerIndex;
        }

        int legIndex() const
        {
                return _legIndex;
        }

private:
        int _playerIndex;
        int _legIndex;
};



#endif // DARTTURNINDEX_H




