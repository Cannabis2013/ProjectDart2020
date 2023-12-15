#include "dartscontrollerbuilder.h"

#include "src/DartsController/Finishes/dartsfinishes.h"
#include "src/DartsController/indexes/dartsindexes.h"
#include "src/DartsController/input/dartsinputadder.h"
#include "src/DartsController/input/dartsinputs.h"
#include "src/DartsController/input/dartsinputstrimmer.h"
#include "src/DartsController/players/dartsplayers.h"
#include "src/DartsController/responses/dartsturnvalues.h"
#include "src/DartsController/scores/dartsscores.h"
#include "src/DartsController/statistics/dartsstatistics.h"
#include "src/DartsController/status/dartsstatus.h"

DartsController* DartsControllerBuilder::build()
{
        auto controller = new DartsController();
        auto indexService = new DartsIndexes();
        auto playerService = new DartsPlayers(indexService);
        auto statusService = new DartsStatus();
        auto inputsService = new DartsInputs(indexService, playerService);
        auto scoresService = new DartsScores(indexService, playerService, inputsService);
        auto evalService = new DartsEvaluators(scoresService, playerService, statusService);
        auto statisticService = new DartsStatistics(inputsService, scoresService, indexService);
        auto finishService = new DartsFinishes();
        auto turnService = new DartsTurnValues(playerService, indexService, statisticService,
            finishService, scoresService, statusService);
        auto inputTrimmerService = new DartsInputsTrimmer(inputsService, indexService);
        auto adderService = new DartsInputAdder(inputsService, inputTrimmerService,
            indexService, statusService);
        controller->setIndexes(indexService);
        controller->setPlayers(playerService);
        controller->setScores(scoresService);
        controller->setEvaluators(evalService);
        controller->setTurnValues(turnService);
        controller->setTrimmer(inputTrimmerService);
        controller->setStatistics(statisticService);
        controller->setStatus(statusService);
        controller->setInputs(inputsService);
        controller->setFinishes(finishService);
        controller->setAdder(adderService);
        controller->setInitializer(new ControllerInitializer(controller));
        return controller;
}
