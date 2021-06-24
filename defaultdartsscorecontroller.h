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
#include "addtotalscoretodartsscoremodel.h"
#include "builddartsscoreturnvalues.h"
#include "JsonBuilder.h"
#include "dartsplayerbuilderservice.h"
#include "jsonmergebybytearrayservice.h"
#include "dartsjsonextractor.h"

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
        controller->_inputService = DartsPlayerScoreService::createInstance(details->keyPoint(),
                                                                               details->winnerId());
        controller->_dartsJsonBuilderService = new DartsScoreJsonBuilderService;
        controller->_determineControllerStateByWinnerId = new DetermineControllerStateByWinnerId;
        controller->_addTotalScoreToModel = new AddTotalScoreToDartsScoreModel;
        controller->_turnValuesBuilder = new buildDartsScoreTurnValues;
        controller->_dartsScoreBuilder = new DartsScoreModelsBuilderService;
        controller->_dartsIndexesBuilderService = new DartsScoreIndexesBuilderService;
        controller->_dartsJsonService = new JsonBuilder;
        controller->_playerBuilderService = new DartsPlayerBuilderService;
        controller->_jsonMergeService = new JsonMergeByByteArrayService;
        controller->_extractJson = new DartsJsonExtractor;
        return controller;
    }
private:
    DefaultDartsScoreController(const QUuid &tournamentId, const int &displayHint):
        DartsScoreController(tournamentId,displayHint)
    {}
};

#endif // DEFAULTDARTSSCORECONTROLLER_H
