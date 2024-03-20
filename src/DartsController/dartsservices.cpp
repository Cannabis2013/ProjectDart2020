#include "dartsservices.h"
#include "servicecollection.h"
#include "src/DartsController/Finishes/dartsfinishes.h"
#include "src/DartsController/input/persistence/dartsinputs.h"
#include "src/DartsController/input/services/dartsinputsfilter.h"
#include "src/DartsController/input/services/dartsinputsupdate.h"
#include "src/DartsController/players/persistences/dartsplayers.h"
#include "src/DartsController/players/services/playerfetcher.h"
#include "src/DartsController/scores/persistence/dartsscores.h"
#include "src/DartsController/scores/services/dartscalculator.h"
#include "src/DartsController/scores/services/dartsscoresfetch.h"
#include "src/DartsController/scores/services/dartsscoresupdate.h"
#include "src/DartsController/statistics/services/dartsinputstatistics.h"
#include "src/DartsController/status/dartsstatus.h"
#include "src/DartsController/turns/persistences/dartsindexes.h"
#include "src/DartsController/validation/dartsevaluators.h"

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
        services->status = new DartsStatus();
        services->inputs = new DartsInputs();
        services->scores = new DartsScores();
}

void DartsServices::injectServices(ServiceCollection* services)
{
        services->calculator = new DartsCalculator();
        services->scoresUpdate = new DartsScoresUpdate(services);
        services->evaluators = new DartsEvaluators(services);
        services->finishes = new DartsFinishes();
        services->scoresFetcher = new DartsScoresFetch(services);
        services->inputsUpdate = new DartsInputsUpdate(services);
        services->inputsFilter = new DartsInputsfilter(services);
        services->inputStatistics = new DartsInputStatistics(services);
        services->playerFetcher = new PlayerFetcher(services);
}
