#include "dartsservices.h"
#include "servicecollection.h"
#include "src/input/dartsinputs.h"
#include "src/input/dartsinputsfilter.h"
#include "src/input/dartsinputsupdater.h"
#include "src/players/dartsplayers.h"
#include "src/scores/dartsreminings.h"
#include "src/statistics/statscalculator.h"
#include "src/turns/dartsindexes.h"
#include "src/validation/dartscloseningfilter.h"
#include "src/validation/openvalidator.h"

ServiceCollection* DartsServices::build()
{
    auto services = new ServiceCollection();

    services->players = new DartsPlayers();
    services->indexes = new DartsIndexes();
    services->inputs = new DartsInputs();
    services->scores = new DartsReminings(services, "initialScore");
    services->inputsFilter = new DartsInputsfilter(services);
    services->inputStatistics = new StatsCalculator(services);
    services->inputsUpdater = new DartsInputsUpdater(services);
    services->openingFilter = new OpenValidator(services);
    services->closeningFilter = new DartsCloseningFilter(services);

    return services;
}
