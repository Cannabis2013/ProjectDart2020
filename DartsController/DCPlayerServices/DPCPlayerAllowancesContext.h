#ifndef DPCPLAYERALLOWANCESCONTEXT_H
#define DPCPLAYERALLOWANCESCONTEXT_H

#include <qdebug.h>

#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
class DPCPlayerAllowancesContext : public IDCPlayerController
{
public:
    virtual void appendPlayerId(const QVector<DCPlayer> &playerModels) override
    {
        for (const auto &playerModel : playerModels) {
            PlayerObject obj;
            obj.playerId = playerModel.id;
            _playerStructs.append(obj);
        }
    }
    virtual bool isAllowedEntrance(const QUuid &playerId) override
    {
        return getPlayerStructFromId(playerId).in;
    }
    virtual void playerIsIn(const QUuid &playerId) override
    {
        try {
            getPlayerStructFromId(playerId).in = true;
        }  catch (...) {
            qDebug() << "Playerstruct not found";
        }
    }
    virtual void reset() override
    {
        for (auto &playerStruct : _playerStructs)
            playerStruct.in = false;
    }
private:
    PlayerObject &getPlayerStructFromId(const QUuid &id)
    {
        for (auto &playerStruct : _playerStructs) {
            if(playerStruct.playerId == id)
                return playerStruct;
        }
        throw "Playerstruct not found";
    }
    QVector<PlayerObject> _playerStructs;
};

#endif // DCPLAYERENTRANCECONTEXT_H
