#ifndef DCMETASERVICES_H
#define DCMETASERVICES_H

#include "idcmetaconverter.h"
#include "idcmetabuilder.h"
#include "idcmetamanager.h"

struct DCMeta;

class DCMetaServices
{
public:
    typedef DCMeta Meta;
    typedef QByteArray ByteArray;
    typedef IDCMetaConverter<Meta> MetaConverter;
    typedef IDCMetaBuilder<Meta> MetaBuilder;
    typedef IDCMetaManager<DCMeta> MetaManager;
    MetaManager *metaManager() const {return _metaInfo;}
    void setMetaContext(MetaManager *service) {_metaInfo = service;}
    MetaBuilder *createMeta() const {return _metaBuilder;}
    void setMetaBuilder(MetaBuilder *service) {_metaBuilder = service;}
    MetaConverter *metaConverter() const {return _metaConverter;}
    void setMetaConverter(MetaConverter *newMetaConverter) {_metaConverter = newMetaConverter;}
private:
    MetaConverter *_metaConverter;
    MetaBuilder *_metaBuilder;
    MetaManager *_metaInfo;
};
#endif // DCMETASERVICES_H
