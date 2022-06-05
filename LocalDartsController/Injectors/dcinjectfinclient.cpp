#include "dcinjectfinclient.h"

#include <DartsController/Finishes/dcfinishesservices.h>
#include <DartsController/ServicesProvider/dcservices.h>
#include <LocalDartsController/Finishes/dartsboundaries.h>
#include <LocalDartsController/Finishes/dartscreatefinishes.h>
#include <LocalDartsController/Finishes/dartsdefaultattempts.h>
#include <LocalDartsController/Finishes/dartsdivisors.h>
#include <LocalDartsController/Finishes/dartsfieldvalues.h>
#include <LocalDartsController/Finishes/dartsmodidentifiers.h>
#include <LocalDartsController/Finishes/dartsterminaldivisor.h>
#include <LocalDartsController/Finishes/dcfinishbuilder.h>
#include <LocalDartsController/Finishes/dclogisticdb.h>
#include <LocalDartsController/Finishes/defaultthresholds.h>

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
