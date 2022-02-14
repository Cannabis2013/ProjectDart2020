#include "dcinjectfinclient.h"
#include "Finishes/dartsconstructslas.h"
#include "Finishes/dcfinishesservices.h"
#include "Finishes/dartsboundaries.h"
#include "Finishes/dartsdefaultattempts.h"
#include "Finishes/dartsdivisors.h"
#include "Finishes/dartsfieldvalues.h"
#include "Finishes/dartsmodidentifiers.h"
#include "Finishes/dartsterminaldivisor.h"
#include "Finishes/defaultthresholds.h"
#include "Finishes/dartscreatefinishes.h"
#include "Finishes/dcfinishbuilder.h"
#include "Finishes/dclogisticdb.h"
#include "ServicesProvider/dcservices.h"

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
    auto constructRows = new DartsCreateFinishes;
    injectConRowClient(constructRows);
    builder->setConstructRow(constructRows);
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
