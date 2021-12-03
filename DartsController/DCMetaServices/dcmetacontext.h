#ifndef DCMETACONTEXT_H
#define DCMETACONTEXT_H
#include "DartsController/DCMetaSLAs/idcmetactx.h"
#include "DartsControllerBuilder/DCBMetaServices/dcbmeta.h"
#include <quuid.h>
class DCMetaContext : public IDCMetaCtx
{
public:
    void set(const QUuid &id, const int &initialRemaining) override
    {
        _meta.tournamentId = id;
        _meta.initRemScore = initialRemaining;
    }
    virtual void set(const int &status) override
    {
        _meta.status = status;
    }
    DCMeta &get() override
    {
        return _meta;
    }
private:
    DCMeta _meta;
};
#endif // DCTOURNAMENTID_H
