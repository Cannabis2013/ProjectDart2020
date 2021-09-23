#ifndef PLAYERWINNERJSONKEYS_H
#define PLAYERWINNERJSONKEYS_H

#include "DartsController/DCPlayerSLAs/idcplayerkeys.h"

class DCWinnerKeys : public IDCPlayerKeys
{
public:
    virtual QString playerId() const override
    {
        return "winnerId";
    }
    virtual QString playerName() const override
    {
        return "winnerName";
    }
};
#endif // PLAYERWINNERJSONKEYS_H
