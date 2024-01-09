#include "dartscontrollerbuilder.h"

#include "src/DartsController/Finishes/dartsfinishes.h"
#include "src/DartsController/controller/dartsturns.h"
#include "src/DartsController/indexes/dartsindexes.h"
#include "src/DartsController/input/dartsinputadder.h"
#include "src/DartsController/input/dartsinputs.h"
#include "src/DartsController/input/dartsinputstrimmer.h"
#include "src/DartsController/players/dartsplayers.h"
#include "src/DartsController/responses/dartsturnvalues.h"
#include "src/DartsController/scores/dartscalculator.h"
#include "src/DartsController/scores/dartsscores.h"
#include "src/DartsController/statistics/dartsstatistics.h"
#include "src/DartsController/status/dartsstatus.h"
#include "src/DartsController/validation/dartsallowances.h"

DartsController* DartsControllerBuilder::build()
{
        auto controller = new DartsController();
        auto allowances = new DartsAllowances();
        auto calculator = new DartsCalculator();
        auto indexes = new DartsIndexes();
        auto player = new DartsPlayers(indexes);
        auto status = new DartsStatus();
        auto inputs = new DartsInputs(indexes, player);
        auto scores = new DartsScores(indexes, player, inputs, calculator);
        auto evaluators = new DartsEvaluators(scores, player, status, calculator, allowances);
        auto statistic = new DartsStatistics(inputs, scores, indexes);
        auto finishes = new DartsFinishes();
        auto turns = new DartsTurns(status, indexes, scores, player, allowances, inputs);
        auto turnValues = new DartsTurnValues(player, indexes, statistic,
            finishes, scores, status);
        auto inputTrimmer = new DartsInputsTrimmer(inputs, indexes);
        auto adderService = new DartsInputAdder(inputs, inputTrimmer,
            indexes, status);
        auto initializer = new ControllerInitializer(controller);
        controller->setIndexes(indexes);
        controller->setPlayers(player);
        controller->setTurns(turns);
        controller->setScores(scores);
        controller->setEvaluators(evaluators);
        controller->setTurnValues(turnValues);
        controller->setTrimmer(inputTrimmer);
        controller->setStatistics(statistic);
        controller->setStatus(status);
        controller->setInputs(inputs);
        controller->setFinishes(finishes);
        controller->setAdder(adderService);
        controller->setAllowances(allowances);
        controller->setInitializer(initializer);
        return controller;
}
