#include "dartscontrollerbuilder.h"

#include "src/DartsController/Finishes/dartsfinishes.h"
#include "src/DartsController/controller/dartsturns.h"
#include "src/DartsController/indexes/dartsindexes.h"
#include "src/DartsController/input/dartsinputadder.h"
#include "src/DartsController/input/dartsinputs.h"
#include "src/DartsController/input/dartsinputstrimmer.h"
#include "src/DartsController/jsonReport/dartsjsonreport.h"
#include "src/DartsController/jsonReport/dartsmessagesreport.h"
#include "src/DartsController/jsonReport/dartsstatusreport.h"
#include "src/DartsController/players/dartsplayers.h"
#include "src/DartsController/scores/dartscalculator.h"
#include "src/DartsController/scores/dartsscores.h"
#include "src/DartsController/scores/dartsscoresreport.h"
#include "src/DartsController/stats/dartsstatsreport.h"
#include "src/DartsController/status/dartsstatus.h"

DartsController* DartsControllerBuilder::build()
{
        auto controller = new DartsController();
        auto calculator = new DartsCalculator();
        auto indexes = new DartsIndexes();
        auto status = new DartsStatus();
        auto players = new DartsPlayers(indexes);
        auto inputs = new DartsInputs(indexes, players);
        auto scores = new DartsScores(indexes, players, inputs, calculator);
        auto evaluators = new DartsEvaluators(scores, players, status, calculator);
        auto trimmer = new DartsInputsTrimmer(inputs, indexes);
        auto turns = new DartsTurns(status, indexes, scores, players, inputs, trimmer);
        auto finishes = new DartsFinishes();
        auto initializer = new ControllerInitializer(controller);
        // Report service
        auto statsReport = new DartsStatsReport(inputs, scores, indexes, calculator, players);
        auto statusReport = new DartsStatusReport(players, indexes, status);
        auto messagesReport = new DartsMessagesReport(finishes, scores, indexes);
        auto scoresReport = new DartsScoresReport(scores);
        auto reportService = new DartsJsonReport(statsReport, scoresReport, statusReport, messagesReport);
        auto adderService = new DartsInputAdder(inputs, trimmer, indexes, status, scores);
        // Inject services
        controller->setIndexes(indexes);
        controller->setPlayers(players);
        controller->setTurns(turns);
        controller->setScores(scores);
        controller->setEvaluators(evaluators);
        controller->setTurnInfo(reportService);
        controller->setStatus(status);
        controller->setInputs(inputs);
        controller->setAdder(adderService);
        controller->setInitializer(initializer);
        return controller;
}
