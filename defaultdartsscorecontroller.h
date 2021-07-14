#ifndef DEFAULTDARTSSCORECONTROLLER_H
#define DEFAULTDARTSSCORECONTROLLER_H

#include "dartsscorecontroller.h"
#include "idartscontrollerentity.h"
#include <quuid.h>
#include "dartssingleattemptinputrowsuggestion.h"
#include "ScoreValidator.h"
#include "dartsplayerscoreservice.h"
#include "dartsscorejsonbuilderservice.h"
#include "dartsscoremodelsbuilderservice.h"
#include "dartsscoreindexesbuilderservice.h"
#include "scoreindexcontroller.h"
#include "determinecontrollerstatebywinnerid.h"
#include "addtotalscoretodartsscoremodel.h"
#include "builddartsscoreturnvalues.h"
#include "DefaultQtJsonBuilder.h"
#include "dartsplayerbuilderservice.h"
#include "jsonmergebybytearrayservice.h"
#include "defaultqtjsonextractor.h"
#include "dartssingleattemptinputrowsuggestion.h"
#include "dartsmetadataservice.h"

class DefaultDartsScoreController : public DartsScoreController
{
public:
    typedef DartsBuilderContext::IDartsControllerEntity<QUuid,QString> ControllerEntity;
    static DefaultDartsScoreController *createInstance(const ControllerEntity *details)
    {
        using namespace DartsScoreControllerContext;
        auto controller = new DefaultDartsScoreController();
        controller->_scoreLogisticInterface = DartsSingleAttemptInputRowSuggestion::createInstance();
        controller->_inputEvaluator = ScoreValidator::createInstance(details->terminalKeyCode());
        controller->_indexService = ScoreIndexController::createInstance();
        controller->_inputService = DartsPlayerScoreService::createInstance(details->keyPoint(),
                                                                               details->winnerId());
        controller->_dartsJsonBuilderService = new DartsScoreJsonBuilderService;
        controller->_determineControllerStateByWinnerId = new DartsControllerContext::DetermineControllerStateByWinnerId;
        controller->_addTotalScoreToModel = new AddTotalScoreToDartsScoreModel;
        controller->_turnValuesBuilder = new buildDartsScoreTurnValues;
        controller->_dartsScoreBuilder = new DartsScoreModelsBuilderService;
        controller->_dartsIndexesBuilderService = new DartsScoreIndexesBuilderService;
        controller->_playerBuilderService = new DartsPlayerBuilderService;
        controller->_jsonMergeService = new JsonMergeByByteArrayService;
        controller->_dartsJsonBuilder = new DefaultQtJsonBuilder;
        controller->_extractJson = new DefaultQtJsonExtractor;
        controller->_metaData = DartsMetaDataService::createInstance(details->tournamentId(),details->displayHint());
        return controller;
    }
};

#endif // DEFAULTDARTSSCORECONTROLLER_H
