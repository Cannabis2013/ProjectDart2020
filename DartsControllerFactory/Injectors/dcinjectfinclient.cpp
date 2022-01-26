#include "dcinjectfinclient.h"
#include "DCFinishesSLAs/dartsconstructslas.h"
#include "DCFinishesSLAs/dcfinishesservices.h"
#include "DCFinishesServices/dartsboundaries.h"
#include "DCFinishesServices/dartsdefaultattempts.h"
#include "DCFinishesServices/dartsdivisors.h"
#include "DCFinishesServices/dartsfieldvalues.h"
#include "DCFinishesServices/dartsmodidentifiers.h"
#include "DCFinishesServices/dartsterminaldivisor.h"
#include "DCFinishesServices/defaultthresholds.h"
#include "DCFinishesServices/dartscreatefinishes.h"
#include "DCFinishesServices/dcfinishbuilder.h"
#include "DCFinishesServices/dclogisticdb.h"
void DCInjectFinClient::inject(DCFinishesSLAs *service) const
{
    auto finBuilder = new DCFinishBuilder;
    injectBuilderClient(finBuilder);
    finBuilder->init();
    service->setFinishBuilder(finBuilder);
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
