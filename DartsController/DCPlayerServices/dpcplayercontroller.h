#ifndef DPCPLAYERCONTROLLER_H
#define DPCPLAYERCONTROLLER_H
#include <qdebug.h>
#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
class DPCPlayerController : public IDCPlayerController
{
public:
    struct PlayerObject{
        bool in;
        QUuid playerId;
    };
    void set(const Players &models) override
    {
        for (const auto &model : models) {
            auto player = dynamic_cast<const IPlayerModel*>(model);
            PlayerObject obj;
            obj.playerId = player->id();
            _playerStructs.append(obj);
        }
    }
    bool status(const QUuid &playerId) const override
    {
        return getPlayerStructFromId(playerId).in;
    }
    bool updateStatus(const QUuid &playerId, const bool &status) override
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
