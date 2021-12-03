#ifndef DPCPLAYERCONTEXT_H
#define DPCPLAYERCONTEXT_H
#include <qdebug.h>
#include "DartsController/DCPlayerSLAs/IDCPlayerCtx.h"
class DPCPlayerContext : public IDCPlayerCtx
{
public:
    void set(const QStringList &names) override
    {
        for (const auto &name : names)
            _players << Player{.name = name,.in = false};
    }
    bool status(const QString &name) const override
    {
        return getPlayer(name).in;
    }
    bool updateStatus(const QString &name, const bool &status) override
    {
        try {
            getPlayer(name).in = status;
        }  catch (...) {
            qDebug() << "Playerstruct not found";
            return false;
        }
        return status;
    }
    void reset() override
    {
        for (auto &playerStruct : _players)
            playerStruct.in = false;
    }
    int count() const override
    {
        return _players.count();
    }
private:
    Player getPlayer(const QString &name) const
    {
        for (auto &player : _players) {
            if(player.name == name)
                return player;
        }
        return Player();
    }
    Player &getPlayer(const QString &name)
    {
        for (auto &player : _players) {
            if(player.name == name)
                return player;
        }
        throw "NOT FOUND";
    }
    QVector<Player> _players;
};
#endif // DCPLAYERENTRANCECONTEXT_H
