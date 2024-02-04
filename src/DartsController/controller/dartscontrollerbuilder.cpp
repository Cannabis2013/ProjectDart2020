#include "dartscontrollerbuilder.h"

#include "src/DartsController/Finishes/dartsfinishes.h"
#include "src/DartsController/controller/dartsturns.h"
#include "src/DartsController/indexes/dartsindexes.h"
#include "src/DartsController/input/dartsinputadder.h"
#include "src/DartsController/input/dartsinputs.h"
#include "src/DartsController/input/dartsinputstrimmer.h"
#include "src/DartsController/players/dartsplayers.h"
#include "src/DartsController/responses/dartsjsonreport.h"
#include "src/DartsController/scores/dartscalculator.h"
#include "src/DartsController/scores/dartsscores.h"
#include "src/DartsController/statistics/dartsstatistics.h"
#include "src/DartsController/status/dartsstatus.h"

DartsController* DartsControllerBuilder::build()
{
        auto controller = new DartsController();
        auto calculator = new DartsCalculator();
        auto indexes = new DartsIndexes();
        auto players = new DartsPlayers(indexes);
        auto status = new DartsStatus();
        auto inputs = new DartsInputs(indexes, players);
        auto scores = new DartsScores(indexes, players, inputs, calculator);
        auto evaluators = new DartsEvaluators(scores, players, status, calculator);
        auto statistic = new DartsStatistics(inputs, scores, indexes, calculator);
        auto finishes = new DartsFinishes();
        auto trimmer = new DartsInputsTrimmer(inputs, indexes);
        auto turns = new DartsTurns(status, indexes, scores, players, inputs, trimmer);
        auto turnInfo = new DartsJsonReport(players, indexes, finishes, scores, status, statistic);
        auto adderService = new DartsInputAdder(inputs, trimmer,indexes, status, scores);
        auto initializer = new ControllerInitializer(controller);
        controller->setIndexes(indexes);
        controller->setPlayers(players);
        controller->setTurns(turns);
        controller->setScores(scores);
        controller->setEvaluators(evaluators);
        controller->setTurnInfo(turnInfo);
        controller->setStatistics(statistic);
        controller->setStatus(status);
        controller->setInputs(inputs);
        controller->setFinishes(finishes);
        controller->setAdder(adderService);
        controller->setInitializer(initializer);
        return controller;
}
