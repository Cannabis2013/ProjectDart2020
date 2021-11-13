#ifndef IDCMETAINFO_H
#define IDCMETAINFO_H
#include <DartsController/DCMetaServices/dcmeta.h>
class IDCMetaInfo
{
public:
    virtual void set(const QUuid &id, const int &initialRemaining) = 0;
    virtual DCMeta &get() = 0;
};
#endif // IDCMETAINFO_H
