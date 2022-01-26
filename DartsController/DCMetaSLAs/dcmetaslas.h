#ifndef DCMETASLAS_H
#define DCMETASLAS_H
#include "idcmetaconverter.h"
#include "idcmetabuilder.h"
#include "idcmetacontext.h"
class DCMetaSLAs
{
public:
    typedef DCMeta Meta;
    typedef QByteArray ByteArray;
    typedef IDCMetaConverter<Meta> MetaConverter;
    typedef IDCMetaBuilder<Meta> MetaBuilder;
    typedef IDCMetaContext<DCMeta> MetaContext;
    MetaContext *metaService() const {return _metaInfo;}
    void setMetaContext(MetaContext *service) {_metaInfo = service;}
    MetaBuilder *createMeta() const {return _metaBuilder;}
    void setMetaBuilder(MetaBuilder *service) {_metaBuilder = service;}
    MetaConverter *metaConverter() const {return _metaConverter;}
    void setMetaConverter(MetaConverter *newMetaConverter) {_metaConverter = newMetaConverter;}
private:
    MetaConverter *_metaConverter;
    MetaBuilder *_metaBuilder;
    MetaContext *_metaInfo;
};
#endif // DCMETASLAS_H
