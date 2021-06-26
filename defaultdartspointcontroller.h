#ifndef DEFAULTDARTSPOINTCONTROLLER_H
#define DEFAULTDARTSPOINTCONTROLLER_H

#include "dartspointcontroller.h"
#include "idartscontrollerentity.h"

#include "CalculateScoreByDartsPointInput.h"
#include "pointvalidator.h"
#include "PointIndexController.h"
#include "dartsplayerpointservice.h"
#include "buildDartsPointTurnValues.h"
#include "dartspointbuilderservice.h"
#include "DartsIndexesBuilderService.h"
#include "dartsplayermodelbuilderservice.h"
#include "dartscontrollerpointmodelsservice.h"
#include "getordereddartspointsbyjson.h"
#include "addtotalscoretodartsinputsjson.h"
#include "addplayernamestodartspointsjson.h"
#include "dartspointinputstojson.h"
#include "jsonmergebybytearrayservice.h"
#include "addtotalscoretodartspoint.h"
#include "DefaultQtJsonBuilder.h"
#include "defaultqtjsonextractor.h"
#include "dartsmetadataservice.h"
#include "dartspointstringsuggestion.h"

namespace DartsBuilderContext {
    class DefaultDartsPointController : public DartsPointControllerContext::DartsPointController
    {
    public:
        typedef IDartsControllerEntity<QUuid,QString> ControllerEntity;
        static DefaultDartsPointController *createInstance(const ControllerEntity *details)
        {
            using namespace DartsPointControllerContext;
            auto tournamentId = details->tournamentId();
            auto displayHint = details->displayHint();
            auto controller = new DefaultDartsPointController();
            controller->_inputEvaluator = PointValidator::createInstance(details->terminalKeyCode());
            controller->_indexService = PointIndexController::createInstance(details->attempts());
            controller->_inputService = DartsPlayerPointService::createInstance(details->keyPoint(),details->winnerId());
            controller->_turnValuesBuilder = new BuildDartsPointTurnValues;
            controller->_pointModelBuilder = new DartsPointBuilderService;
            controller->_dartsIndexesBuilder = new DartsIndexesBuilderService;
            controller->_controllerModels = new DartsControllerPointModelsService;
            controller->_playerModelBuilder = new DartsPlayerModelBuilderService;
            controller->_getOrderedDartsPointsByJson = new GetOrderedDartsPointsByJson;
            controller->_addTotalScoresToDartsModelsJson = new AddTotalScoreToDartsInputsJson;
            controller->_dartsPointsToJson = new DartsPointInputsToJson;
            controller->_calculateScoreByPointInput = new CalculateScoreByDartsPointInput;
            controller->_jsonMerger = new JsonMergeByByteArrayService;
            controller->_addPlayerNamesToDartsModelsJson = new AddPlayerNamestoDartsPointsJson;
            controller->_addTotalScoreToPointModel = new AddTotalScoreToDartsPoint;
            controller->_jsonBuilder = new DefaultQtJsonBuilder;
            controller->_jsonExtractor = new DefaultQtJsonExtractor;
            controller->_metaData = DartsMetaDataService::createInstance(tournamentId,displayHint);
            controller->_stringSuggestionService = DartsPointStringSuggestion::createInstance(details->attempts());
            return controller;
        }
    };
}

#endif // DEFAULTDARTSPOINTCONTROLLER_H
