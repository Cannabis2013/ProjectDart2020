#ifndef DARTTURNINDEX_H
#define DARTTURNINDEX_H

#include "dartsindex.h"

class DartsTurnIndex
{
public:
        DartsTurnIndex(const DartsIndex &index){
                _playerIndex = index.playerIndex;
                _roundIndex = index.roundIndex;
                _turnId = index.turnCount;
        }

        QJsonObject object() const
        {
                QJsonObject jsonObj;
                jsonObj["roundIndex"] = _roundIndex;
                jsonObj["turnIndex"] = _playerIndex;
                jsonObj["turnId"] = _turnId;
                return jsonObj;
        }

        int playerIndex() const
        {
                return _playerIndex;
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
        int _playerIndex;
        int _turnId;
        int _roundIndex;
};
#endif // DARTTURNINDEX_H
