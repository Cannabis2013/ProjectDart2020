#ifndef DCMETAINFO_H
#define DCMETAINFO_H
#include "DartsController/DCMetaSLAs/idcmetainfo.h"
#include "DartsControllerBuilder/DCBMetaServices/dcbmeta.h"
#include <quuid.h>
class DCMetaInfo : public IDCMetaInfo
{
public:
    DCMetaInfo(const QUuid &id, const int &initialRemaining)
    {
        _meta.tournamentId = id;
        _meta.initialRemainingScore = initialRemaining;
    }
    virtual DCMeta &get() override
    {
        return _meta;
    }
private:
    DCMeta _meta;
};

#endif // DCTOURNAMENTID_H
