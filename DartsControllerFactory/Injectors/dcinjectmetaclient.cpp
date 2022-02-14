#include "dcinjectmetaclient.h"
#include "Meta/dcmetabuilder.h"
#include "Meta/dcmetaconverter.h"
#include "ServicesProvider/dcservices.h"

#include "Meta/dcmetaservice.h"
void DCInjectMetaClient::inject(DCServices *services) const
{
    auto MetaServices = new DCMetaServices;
    MetaServices->setMetaContext(new DCMetaService);
    MetaServices->setMetaBuilder(new DCMetaBuilder);
    MetaServices->setMetaConverter(new DCMetaConverter);
    services->setMetaServices(MetaServices);
}
