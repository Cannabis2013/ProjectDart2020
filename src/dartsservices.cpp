#include "dartsservices.h"
#include "servicecollection.h"
#include "src/Finishes/dartsfinishes.h"
#include "src/input/persistence/dartsinputs.h"
#include "src/input/services/dartsinputsfilter.h"
#include "src/input/services/dartsinputsupdater.h"
#include "src/players/persistences/dartsplayers.h"
#include "src/players/services/playerfetcher.h"
#include "src/scores/services/dartsscores.h"
#include "src/statistics/services/statscalculator.h"
#include "src/turns/persistences/dartsindexes.h"
#include "src/validation/persistence/jsonopenpersistence.h"
#include "src/validation/services/dartscloseningfilter.h"
#include "src/validation/services/openvalidator.h"

ServiceCollection* DartsServices::build()
{
    auto services = new ServiceCollection();
    injectPersistences(services);
    injectServices(services);
    return services;
}

void DartsServices::injectPersistences(ServiceCollection* services)
{
    services->players = new DartsPlayers("players.dat");
    services->indexes = new DartsIndexes();
    services->inputs = new DartsInputs("dartsInputs.dat");
    services->scores = new DartsScores(services, "initialScore");
}

void DartsServices::injectServices(ServiceCollection* services)
{
    services->finishes = new DartsFinishes();
    services->inputsFilter = new DartsInputsfilter(services);
    services->inputStatistics = new StatsCalculator(services);
    services->playerFetcher = new PlayerFetcher(services);
    services->inputsUpdater = new DartsInputsUpdater(services);
    services->openingFilter = new OpenValidator(services);
    services->closeningFilter = new DartsCloseningFilter(services);
    services->openPersistence = new JsonOpenPersistence();
}
