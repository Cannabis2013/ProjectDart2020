#ifndef DCMETASLAS_H
#define DCMETASLAS_H
#include "idcmetabuilder.h"
#include "idcmetacontext.h"
class DCMetaSLAs
{
public:
    typedef DCMeta Meta;
    typedef QByteArray ByteArray;
    typedef IDCMetaConverter<Meta,ByteArray> MetaConverter;
    typedef IDCMetaBuilder<Meta,ByteArray> MetaBuilder;
    IDCMetaContext *metaCtx() const {return _metaInfo;}
    void setMetaContext(IDCMetaContext *service) {_metaInfo = service;}
    MetaBuilder *createMeta() const {return _metaBuilder;}
    void setMetaBuilder(MetaBuilder *service) {_metaBuilder = service;}
    MetaConverter *metaConverter() const {return _metaConverter;}
    void setMetaConverter(MetaConverter *newMetaConverter) {_metaConverter = newMetaConverter;}
private:
    MetaConverter *_metaConverter;
    MetaBuilder *_metaBuilder;
    IDCMetaContext *_metaInfo;
};
#endif // DCMETASLAS_H
