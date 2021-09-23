#ifndef IDCPLAYERKEYS_H
#define IDCPLAYERKEYS_H
#include <qstring.h>
class IDCPlayerKeys
{
public:
    virtual QString playerId() const = 0;
    virtual QString playerName() const = 0;
};
#endif // IDCPLAYERKEYS_H
