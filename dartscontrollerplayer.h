#ifndef DARTSCONTROLLERPLAYER_H
#define DARTSCONTROLLERPLAYER_H

#include "idartscontrollerplayer.h"
#include <quuid.h>
namespace DartsPointControllerContext {
    class DartsControllerPlayer : public IDartsControllerPlayer<QUuid,QString> {

        // IDartsControllerPlayer interface
    public:
        static DartsControllerPlayer* createInstance()
        {
            return new DartsControllerPlayer;
        }
        IdFormat playerId() const override
        {
            return _playerId;
        }
        StringFormat playerName() const override
        {
            return _playerName;
        }
        void setPlayerId(const IdFormat &newPlayerId)
        {
            _playerId = newPlayerId;
        }

        void setPlayerName(const StringFormat &newPlayerName)
        {
            _playerName = newPlayerName;
        }

    private:
        IdFormat _playerId;
        StringFormat _playerName;
    };









}

#endif // DARTSCONTROLLERPLAYER_H
