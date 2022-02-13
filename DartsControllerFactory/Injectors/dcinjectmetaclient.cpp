#include "dcinjectmetaclient.h"
#include "DCMetaServices/dcmetabuilder.h"
#include "DCMetaServices/dcmetaconverter.h"
#include "ServicesProvider/dcservices.h"

#include "DCMetaServices/dcmetaservice.h"
void DCInjectMetaClient::inject(DCServices *services) const
{
    auto MetaServices = new DCMetaServices;
    MetaServices->setMetaContext(new DCMetaService);
    MetaServices->setMetaBuilder(new DCMetaBuilder);
    MetaServices->setMetaConverter(new DCMetaConverter);
    services->setMetaServices(MetaServices);
}
