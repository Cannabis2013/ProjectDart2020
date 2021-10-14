#ifndef IDCINPUTJSONKEYS_H
#define IDCINPUTJSONKEYS_H

#include <qstring.h>

class IDCInputJsonKeys
{
public:
    virtual QString playerId() const = 0;
    virtual QString playerName() const = 0;
    virtual QString modKeyCode() const = 0;
    virtual QString point() const = 0;
    virtual QString score() const = 0;
    virtual QString totalScore() const = 0;
};

#endif // IDCINPUTJSONKEYS_H
