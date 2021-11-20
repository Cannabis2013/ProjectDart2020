#ifndef IDCMETACTX_H
#define IDCMETACTX_H
#include <DartsController/DCMetaServices/dcmeta.h>
class IDCMetaCtx
{
public:
    virtual void set(const QUuid &id, const int &initialRemaining) = 0;
    virtual void set(const int &status) = 0;
    virtual DCMeta &get() = 0;
};
#endif // IDCMETACTX_H
