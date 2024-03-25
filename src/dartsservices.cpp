#include "dartsservices.h"
#include "servicecollection.h"
#include "src/Finishes/dartsfinishes.h"
#include "src/input/persistence/dartsinputs.h"
#include "src/input/services/dartsinputsfilter.h"
#include "src/input/services/dartsinputsupdater.h"
#include "src/players/persistences/dartsplayers.h"
#include "src/players/services/playerfetcher.h"
#include "src/scores/persistence/dartsscores.h"
#include "src/scores/services/dartscalculator.h"
#include "src/scores/services/dartsscoresdelta.h"
#include "src/scores/services/dartsscoresfetch.h"
#include "src/scores/services/dartsscoresupdate.h"
#include "src/statistics/services/statscalculator.h"
#include "src/status/dartsstatus.h"
#include "src/turns/persistences/dartsindexes.h"
#include "src/turns/services/dartsindexreport.h"
#include "src/validation/dartsevaluators.h"

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
        services->status = new DartsStatus("status.dat");
        services->inputs = new DartsInputs("dartsInputs.dat");
        services->scores = new DartsScores("initialScore.dat", "initialScore");
}

void DartsServices::injectServices(ServiceCollection* services)
{
        services->calculator = new DartsCalculator();
        services->scoresUpdate = new DartsScoresUpdate(services);
        services->evaluators = new DartsEvaluators(services);
        services->finishes = new DartsFinishes();
        services->scoresFetcher = new DartsScoresFetch(services);
        services->inputsFilter = new DartsInputsfilter(services);
        services->inputStatistics = new StatsCalculator(services);
        services->playerFetcher = new PlayerFetcher(services);
        services->inputsUpdater = new DartsInputsUpdater(services);
        services->indexReport = new DartsIndexReport(services);
        services->scoresDelta = new DartsScoresDelta(services);
}
