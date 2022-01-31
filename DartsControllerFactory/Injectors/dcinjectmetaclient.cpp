#include "dcinjectmetaclient.h"
#include "DCMetaSLAs/dcmetaslas.h"
#include "DCMetaServices/dcmetabuilder.h"
#include "DCMetaServices/dcmetaservice.h"
#include "DCMetaServices/dcmetaconverter.h"
void DCInjectMetaClient::inject(DCMetaSLAs *metaServices) const
{
    metaServices->setMetaContext(new DCMetaService);
    metaServices->setMetaBuilder(new DCMetaBuilder);
    metaServices->setMetaConverter(new DCMetaConverter);
}
