#include "buildmultiattemptscorecontroller.h"

using namespace DartsBuilderContext;

BuildMultiAttemptScoreController::ControllerInterface BuildMultiAttemptScoreController::buildSingleAttemptPointController(ControllerDetails details) const
{
    using namespace DartsScoreMultiAttemptContext;
    AbstractDartsScoreController* controller =
            DartsScoreMultiAttemptContext::DartsScoreMultiAttempt::createInstance(details->tournamentId())
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
            ->setPlayerBuilderService(new DartsPlayerBuilderService);
    return controller;
}
