#ifndef DCWINNERSERVICE_H
#define DCWINNERSERVICE_H

#include "DartsController/DCMetaSLAs/idcwinnerservice.h"
#define INCONSISTENCY_EXCEPTION_MESSAGE "User inconsistency!"

class DCWinnerService : public IDCWinnerService
{
public:
    virtual void setWinner(const DCPlayer &winner) override
    {
        _winner = winner;
    }
    virtual void setWinner(const DCInput &input) override
    {
        _winner.id = input.playerId;
        _winner.name = input.playerName;
    }
    virtual DCPlayer &get() override
    {
        return _winner;
    }
private:
    DCPlayer _winner;
};
#endif
