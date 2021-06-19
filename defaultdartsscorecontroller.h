#ifndef DEFAULTDARTSSCORECONTROLLER_H
#define DEFAULTDARTSSCORECONTROLLER_H

#include "dartsscorecontroller.h"
#include "idartscontrollerentity.h"
#include <quuid.h>
#include "dartsscorelogisticcontroller.h"
#include "ScoreValidator.h"
#include "dartsplayerscoreservice.h"
#include "dartsscorejsonbuilderservice.h"
#include "dartsscoremodelsbuilderservice.h"
#include "dartsscoreindexesbuilderservice.h"
#include "scoreindexcontroller.h"
#include "determinecontrollerstatebywinnerid.h"
#include "addaccumulatedscoretodartsscore.h"
#include "assembledartsscoreturnvalues.h"
#include "DartsScoreJsonExtractor.h"
#include "dartsplayerbuilderservice.h"

class DefaultDartsScoreController : public DartsScoreController
{
public:
    typedef DartsBuilderContext::IDartsControllerEntity<QUuid,QString> ControllerEntity;
    static DefaultDartsScoreController *createInstance(const ControllerEntity *details)
    {
        using namespace DartsScoreControllerContext;
        auto controller = new DefaultDartsScoreController(details->tournamentId(),details->displayHint());
        controller->_scoreLogisticInterface = DartsScoreLogisticController::createInstance(details->attempts(),
                                                                                           details->terminalKeyCode());
        controller->_inputEvaluator = ScoreValidator::createInstance(details->terminalKeyCode());
        controller->_indexService = ScoreIndexController::createInstance();
        controller->_scoreController = DartsPlayerScoreService::createInstance(details->keyPoint(),
                                                                               details->winnerId());
        controller->_dartsJsonBuilderService = new DartsScoreJsonBuilderService;
        controller->_determineControllerStateByWinnerId = new DetermineControllerStateByWinnerId;
        controller->_addAccumulatedScoreToModel = new AddAccumulatedScoreToDartsScore;
        controller->_turnValuesBuilderService = new AssembleDartsScoreTurnValues;
        controller->_dartsScoreBuilderService = new DartsScoreModelsBuilderService;
        controller->_dartsIndexesBuilderService = new DartsScoreIndexesBuilderService;
        controller->_dartsJsonExtractorService = new DartsScoreJsonExtractor;
        controller->_playerBuilderService = new DartsPlayerBuilderService;
        return controller;
    }
private:
    DefaultDartsScoreController(const QUuid &tournamentId, const int &displayHint):
        DartsScoreController(tournamentId,displayHint)
    {}
};

#endif // DEFAULTDARTSSCORECONTROLLER_H
