#include "buildmultiattemptscorecontroller.h"

using namespace DartsBuilderContext;

BuildMultiAttemptScoreController::ControllerInterface BuildMultiAttemptScoreController::buildController(ControllerDetails details) const
{
    using namespace DartsScoreControllerContext;
    AbstractDartsScoreController* controller =
            DartsScoreControllerContext::DartsScoreController::createInstance(details->tournamentId())
            ->setLogisticInterface(DartsScoreLogisticController::createInstance(details->attempts(),
                                                                                details->terminalKeyCode()))
            ->setInputValidator(ScoreValidator::createInstance(details->terminalKeyCode()))
            ->setIndexController(ScoreIndexController::createInstance())
            ->setScoreController(DartsPlayerScoreService::createInstance(details->keyPoint(),
                                                                         details->winnerId()))
            ->setJsonService(new DartsScoreJsonBuilderService)
            ->setDetermineControllerStateByWinnerId(new DetermineControllerStateByWinnerId)
            ->setAddAccumulatedScoreToModel(new AddAccumulatedScoreToDartsScore)
            ->setTurnValuesBuilderService(new AssembleDartsScoreTurnValues)
            ->setDartsScoreBuilderService(new DartsScoreModelsBuilderService)
            ->setDartsIndexesBuilderService(new DartsScoreIndexesBuilderService)
            ->setDartsJsonExtractorService(new DartsScoreJsonExtractor)
            ->setPlayerBuilderService(new DartsPlayerBuilderService)
            ->setDisplayHint(details->displayHint());
    return controller;
}
