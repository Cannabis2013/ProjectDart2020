#ifndef IDCINDEXESJSONKEYS_H
#define IDCINDEXESJSONKEYS_H

#include <qstring.h>

class IDCIndexesJsonKeys
{
public:
    virtual QString totalTurns() const = 0;
    virtual QString turnIndex() const = 0;
    virtual QString roundIndex() const = 0;
    virtual QString setIndex() const = 0;
    virtual QString attemptIndex() const = 0;
};
#endif // IDCINDEXESJSONKEYS_H
