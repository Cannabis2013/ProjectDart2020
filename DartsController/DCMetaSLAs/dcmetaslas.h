#ifndef DCMETASLAS_H
#define DCMETASLAS_H
#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
#include "DartsController/DCMetaSLAs/idcmetainfo.h"
#include "idcmetamodelbuilder.h"
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
    IDCMetaInfo *metaInfo() const
    {
        return _metaInfo;
    }
    void setMetaInfo(IDCMetaInfo *service)
    {
        _metaInfo = service;
    }
    IDCMetaModelBuilder *createMeta() const
    {
        return _metaBuilder;
    }
    void setMetaBuilder(IDCMetaModelBuilder *service)
    {
        _metaBuilder = service;
    }
private:
    IDCMetaModelBuilder *_metaBuilder;
    IDartsStatusCodes *_statusCodes;
    IDCMetaInfo *_metaInfo;
};
#endif // DCMETASLAS_H
