#ifndef DINDEXESJSONKEYS_H
#define DINDEXESJSONKEYS_H

#include <DartsModelsContext/DMCIndexesSLAs/IDCIndexesJsonKeys.h>

class DCIndexesJsonKeys : public IDCIndexesJsonKeys
{
    // IDCIndexesJsonKeys interface
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
#endif // DINDEXESJSONKEYS_H
