#include "dartsservices.h"
#include "servicecollection.h"
#include "src/DartsController/Finishes/dartsfinishes.h"
#include "src/DartsController/indexes/dartsindexes.h"
#include "src/DartsController/input/dartsinputs.h"
#include "src/DartsController/input/dartsinputstrimmer.h"
#include "src/DartsController/players/dartsplayers.h"
#include "src/DartsController/scores/dartscalculator.h"
#include "src/DartsController/scores/dartsscores.h"
#include "src/DartsController/status/dartsstatus.h"
#include "src/DartsController/validation/dartsevaluators.h"

ServiceCollection* DartsServices::build()
{
        auto services = new ServiceCollection();
        services->indexes = new DartsIndexes();
        services->status = new DartsStatus();
        services->inputs = new DartsInputs(services);
        services->trimmer = new DartsInputsTrimmer(services);
        services->players = new DartsPlayers(services);
        services->calculator = new DartsCalculator();
        services->scores = new DartsScores(services);
        services->evaluators = new DartsEvaluators(services);
        services->finishes = new DartsFinishes();
        return services;
}
