#ifndef IJSONKEYPLAYER_H
#define IJSONKEYPLAYER_H
#include <qstring.h>
class IJsonKeysPlayer
{
public:
    virtual QString playerId() const = 0;
    virtual QString playerName() const = 0;
};
#endif // IJSONKEYPLAYER_H
