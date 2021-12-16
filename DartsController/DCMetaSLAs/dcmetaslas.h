#ifndef DCMETASLAS_H
#define DCMETASLAS_H
#include "DartsController/DCMetaSLAs/idcmetacontext.h"
#include "abstractdcmetabuilder.h"
class DCMetaSLAs
{
public:
    IDCMetaContext *metaCtx() const {return _metaInfo;}
    void setMetaContext(IDCMetaContext *service) {_metaInfo = service;}
    AbstractDCMetaBuilder *createMeta() const {return _metaBuilder;}
    void setMetaBuilder(AbstractDCMetaBuilder *service) {_metaBuilder = service;}
private:
    AbstractDCMetaBuilder *_metaBuilder;
    IDCMetaContext *_metaInfo;
};
#endif // DCMETASLAS_H
