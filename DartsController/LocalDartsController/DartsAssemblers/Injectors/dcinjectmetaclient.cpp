#include "dcinjectmetaclient.h"

#include <DartsController/Contracts/Meta/dcmetaservices.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>
#include <DartsController/LocalDartsController/Meta/dcmetabuilder.h>
#include <DartsController/LocalDartsController/Meta/dcmetaconverter.h>
#include <DartsController/LocalDartsController/Meta/dcmetaservice.h>

void DCInjectMetaClient::inject(DCServices *services) const
{
        auto MetaServices = new DCMetaServices;
        MetaServices->setMetaContext(new DCMetaService);
        MetaServices->setMetaBuilder(new DCMetaBuilder);
        MetaServices->setMetaConverter(new DCMetaConverter);
        services->setMetaServices(MetaServices);
}
