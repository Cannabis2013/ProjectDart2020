#ifndef IDCMETAINFO_H
#define IDCMETAINFO_H
#include <DartsController/DCMetaServices/dcmeta.h>
class IDCMetaInfo
{
public:
    virtual DCMeta &get() = 0;
};
#endif // IDCMETAINFO_H
