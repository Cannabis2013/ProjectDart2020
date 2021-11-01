#ifndef DCMETASLAS_H
#define DCMETASLAS_H
#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
#include "DartsController/DCMetaSLAs/idcmetainfo.h"
#include "idcmetajsonbuilder.h"
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
    IDCMetaJsonBuilder *setMetaJsonValues() const
    {
        return _setMetaJsonValues;
    }
    void setSetMetaJsonValues(IDCMetaJsonBuilder *service)
    {
        _setMetaJsonValues = service;
    }
    IDCMetaModelBuilder *metaBuilder() const
    {
        return _metaBuilder;
    }
    void setMetaBuilder(IDCMetaModelBuilder *service)
    {
        _metaBuilder = service;
    }
private:
    IDCMetaModelBuilder *_metaBuilder;
    IDCMetaJsonBuilder *_setMetaJsonValues;
    IDartsStatusCodes *_statusCodes;
    IDCMetaInfo *_metaInfo;
};
#endif // DCMETASLAS_H
