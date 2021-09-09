#ifndef DCPLAYERKEYS_H
#define DCPLAYERKEYS_H

#include "ijsonkeyplayer.h"

class DCPlayerKeys : public IJsonKeysPlayer
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
