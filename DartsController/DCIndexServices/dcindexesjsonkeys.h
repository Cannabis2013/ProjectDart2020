#ifndef DCINDEXESJSONKEYS_H
#define DCINDEXESJSONKEYS_H

#include "DartsController/DCIndexSLAs/IDCIndexesJsonKeys.h"

class DCIndexesJsonKeys : public IDCIndexesJsonKeys
{
public:
    virtual QString totalTurns() const override
    {
        return "totalTurns";
    }
    virtual QString turnIndex() const override
    {
        return "turnIndex";
    }
    virtual QString roundIndex() const override
    {
        return "roundIndex";
    }
    virtual QString setIndex() const override
    {
        return "setIndex";
    }
    virtual QString attemptIndex() const override
    {
        return "attemptIndex";
    }
};
#endif // DCINDEXESJSONKEYS_H