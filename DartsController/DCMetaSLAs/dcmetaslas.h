#ifndef DCMETASLAS_H
#define DCMETASLAS_H
#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
#include "DartsController/DCMetaSLAs/idcmetactx.h"
#include "abstractdcmetabuilder.h"
class DCMetaSLAs
{
public:
    IDartsStatusCodes *statusCodes() const
    {
        return _statusCodes;
    }
    void setStatusCodes(IDartsStatusCodes *service)
    {
        _statusCodes = service;
    }
    IDCMetaCtx *metaCtx() const
    {
        return _metaInfo;
    }
    void setMetaContext(IDCMetaCtx *service)
    {
        _metaInfo = service;
    }
    AbstractDCMetaBuilder *createMeta() const
    {
        return _metaBuilder;
    }
    void setMetaBuilder(AbstractDCMetaBuilder *service)
    {
        _metaBuilder = service;
    }
private:
    AbstractDCMetaBuilder *_metaBuilder;
    IDartsStatusCodes *_statusCodes;
    IDCMetaCtx *_metaInfo;
};
#endif // DCMETASLAS_H
