#ifndef DPCPLAYERCONTROLLER_H
#define DPCPLAYERCONTROLLER_H
#include <qdebug.h>
#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
class DPCPlayerController : public IDCPlayerController
{
public:
    void appendPlayerId(const QVector<DCPlayer> &playerModels) override
    {
        for (const auto &playerModel : playerModels) {
            PlayerObject obj;
            obj.playerId = playerModel.id;
            _playerStructs.append(obj);
        }
    }
    bool isIn(const QUuid &playerId) const override
    {
        return getPlayerStructFromId(playerId).in;
    }
    bool updatePlayerStatus(const QUuid &playerId, const bool &status) override
    {
        try {
            getPlayerStructFromId(playerId).in = status;
        }  catch (...) {
            qDebug() << "Playerstruct not found";
        }
        return status;
    }
    void reset() override
    {
        for (auto &playerStruct : _playerStructs)
            playerStruct.in = false;
    }
    int count() const override
    {
        return _playerStructs.count();
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
    const PlayerObject getPlayerStructFromId(const QUuid &id) const
    {
        for (const auto &playerStruct : _playerStructs) {
            if(playerStruct.playerId == id)
                return playerStruct;
        }
        throw "Playerstruct not found";
    }
    QVector<PlayerObject> _playerStructs;
};

#endif // DCPLAYERENTRANCECONTEXT_H
