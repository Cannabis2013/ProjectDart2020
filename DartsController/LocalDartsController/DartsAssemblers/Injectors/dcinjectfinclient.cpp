#include "dcinjectfinclient.h"

#include <DartsController/Contracts/Finishes/dcfinishesservices.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>
#include <DartsController/LocalDartsController/Finishes/dcfinishbuilder.h>
#include <DartsController/LocalDartsController/Finishes/dartsboundaries.h>
#include <DartsController/LocalDartsController/Finishes/dartscreatefinishes.h>
#include <DartsController/LocalDartsController/Finishes/dartsdefaultattempts.h>
#include <DartsController/LocalDartsController/Finishes/dartsdivisors.h>
#include <DartsController/LocalDartsController/Finishes/dartsfieldvalues.h>
#include <DartsController/LocalDartsController/Finishes/dartsmodidentifiers.h>
#include <DartsController/LocalDartsController/Finishes/dartsterminaldivisor.h>
#include <DartsController/LocalDartsController/Finishes/dcfinishbuilder.h>
#include <DartsController/LocalDartsController/Finishes/dclogisticdb.h>
#include <DartsController/LocalDartsController/Finishes/defaultthresholds.h>

void DCInjectFinClient::inject(DCServices *services) const
{
            auto finServices = new DCFinishServices;
            auto finBuilder = new DCFinishBuilder;
            injectBuilderClient(finBuilder);
            finBuilder->init();
            finServices->setFinishBuilder(finBuilder);
            services->setFinServices(finServices);
}

void DCInjectFinClient::injectBuilderClient(DCFinishBuilder *builder) const
{
            auto createFinishes = new DartsCreateFinishes;
            injectConRowClient(createFinishes);
            builder->setConstructRow(createFinishes);
            builder->setDbContext(new DCLogisticDb);
}

void DCInjectFinClient::injectConRowClient(DartsConstructSLAs *service) const
{
            service->setBoundariesService(new DartsBoundaries);
            service->setFieldValuesService(new DartsFieldValues);
            service->setDivisorsService(new DartsDivisors);
            service->setTerminalDivisorService(new DartsTerminalDivisor);
            service->setIdentifiersService(new DartsModIdentifiers);
            service->setAttemptsService(new DartsDefaultAttempts);
            service->setThresholds(new DefaultThresholds);
}
