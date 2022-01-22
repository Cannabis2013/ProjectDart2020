#include "dcinjectmetaclient.h"
#include "DCMetaSLAs/dcmetaslas.h"
#include "DCMetaServices/dcmetabuilder.h"
#include "DCMetaServices/dcmetacontext.h"
#include "DCMetaServices/dcmetaconverter.h"
void DCInjectMetaClient::inject(DCMetaSLAs *metaServices) const
{
    metaServices->setMetaContext(new DCMetaContext);
    metaServices->setMetaBuilder(new DCMetaBuilder);
    metaServices->setMetaConverter(new DCMetaConverter);
}
