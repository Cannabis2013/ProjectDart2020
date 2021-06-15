#include "buildsingleattemptpointcontroller.h"
using namespace DartsBuilderContext;

BuildSingleAttemptPointController::ControllerInterface DartsBuilderContext::BuildSingleAttemptPointController::buildController(ControllerDetails details) const
{
    using namespace DartsPointControllerContext;
    AbstractDartsPointController* controller = DartsPointController::createInstance(details->tournamentId())
            ->setLogisticInterface(DartsPointLogisticController::createInstance(details->attempts(),
                                                                                details->terminalKeyCode()))
            ->setScoreCalculator(DartsPointCalculator::createInstance())
            ->setInputValidator(PointValidator::createInstance(details->terminalKeyCode()))
            ->setIndexController(PointIndexController::createInstance(details->attempts()))
            ->setInputController(DartsPlayerPointService::createInstance(details->keyPoint(),details->winnerId()))
            ->setDartsJsonModelsService(new DartsPointJsonService)
            ->setAssembleDartsPointTurnValues(new BuildDartsPointTurnValues)
            ->setDartsPointBuilderService(new DartsControllerPointBuilder)
            ->setBuildDartsIndexesByJson(new DartsIndexesBuilderService)
            ->setControllerModelsService(new DartsControllerPointModelsService)
            ->setPlayerModelBuilderService(new DartsPlayerModelBuilderService)
            ->setDisplayHint(details->displayHint());
    return controller;
}
