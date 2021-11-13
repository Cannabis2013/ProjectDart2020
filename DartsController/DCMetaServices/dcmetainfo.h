#ifndef DCMETAINFO_H
#define DCMETAINFO_H
#include "DartsController/DCMetaSLAs/idcmetainfo.h"
#include "DartsControllerBuilder/DCBMetaServices/dcbmeta.h"
#include <quuid.h>
class DCMetaInfo : public IDCMetaInfo
{
public:
    void set(const QUuid &id, const int &initialRemaining) override
    {
        _meta.tournamentId = id;
        _meta.initialRemainingScore = initialRemaining;
    }
    DCMeta &get() override
    {
        return _meta;
    }
private:
    DCMeta _meta;
};
#endif // DCTOURNAMENTID_H
