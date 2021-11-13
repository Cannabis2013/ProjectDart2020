#ifndef DSCPLAYERCONTROLLER_H
#define DSCPLAYERCONTROLLER_H
#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
class DSCPlayerController : public IDCPlayerController
{
public:
    virtual void set(const Players &players) override {_players = players;}
    virtual bool status(const QUuid &) const override {return true;}
    virtual bool updateStatus(const QUuid &, const bool &) override{return true;}
    virtual int count() const override {return _players.count();}
    virtual void reset() override{}
private:
    Players _players;
};
#endif // DSCPLAYERCONTROLLER_H
