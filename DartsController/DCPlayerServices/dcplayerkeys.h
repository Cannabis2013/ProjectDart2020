#ifndef DCPLAYERKEYS_H
#define DCPLAYERKEYS_H

#include "DartsController/DCPlayerSLAs/idcplayerkeys.h"

class DCPlayerKeys : public IDCPlayerKeys
{
public:
    virtual QString playerId() const override
    {
        return "playerId";
    }
    virtual QString playerName() const override
    {
        return "playerName";
    }
};
#endif // DEFAULTPLAYERKEYS_H
