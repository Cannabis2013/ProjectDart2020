#ifndef DSCPLAYERCONTROLLER_H
#define DSCPLAYERCONTROLLER_H
#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
class DSCPlayerController : public IDCPlayerController
{
    // IDCPlayerController interface
public:
    virtual void appendPlayerId(const QVector<DCPlayer> &players) override {_players = players;}
    virtual bool isIn(const QUuid &) const override {return true;}
    virtual bool updatePlayerStatus(const QUuid &, const bool &) override{return true;}
    virtual int count() const override {return _players.count();}
    virtual void reset() override{}
private:
    QVector<DCPlayer> _players;
};
#endif // DSCPLAYERCONTROLLER_H
