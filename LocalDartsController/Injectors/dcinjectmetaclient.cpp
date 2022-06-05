#include "dcinjectmetaclient.h"

#include <DartsController/Meta/dcmetaservices.h>
#include <DartsController/ServicesProvider/dcservices.h>
#include <LocalDartsController/Meta/dcmetabuilder.h>
#include <LocalDartsController/Meta/dcmetaconverter.h>
#include <LocalDartsController/Meta/dcmetaservice.h>

void DCInjectMetaClient::inject(DCServices *services) const
{
        auto MetaServices = new DCMetaServices;
        MetaServices->setMetaContext(new DCMetaService);
        MetaServices->setMetaBuilder(new DCMetaBuilder);
        MetaServices->setMetaConverter(new DCMetaConverter);
        services->setMetaServices(MetaServices);
}
