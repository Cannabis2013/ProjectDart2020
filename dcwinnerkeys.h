#ifndef PLAYERWINNERJSONKEYS_H
#define PLAYERWINNERJSONKEYS_H

#include "ijsonkeyplayer.h"

class DCWinnerKeys : public IJsonKeysPlayer
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
