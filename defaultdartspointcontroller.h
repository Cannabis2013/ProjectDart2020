#ifndef DEFAULTDARTSPOINTCONTROLLER_H
#define DEFAULTDARTSPOINTCONTROLLER_H

#include "dartspointcontroller.h"
#include "idartscontrollerentity.h"

#include "CalculateScoreByDartsPointInput.h"
#include "pointvalidator.h"
#include "PointIndexController.h"
#include "dartspointjsonservice.h"
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


namespace DartsBuilderContext {
    class DefaultDartsPointController : public DartsPointControllerContext::DartsPointController
    {
    public:
        typedef IDartsControllerEntity<QUuid,QString> ControllerEntity;
        static DefaultDartsPointController *createInstance(const ControllerEntity *details)
        {
            using namespace DartsPointControllerContext;
            auto controller = new DefaultDartsPointController(details->tournamentId(),details->displayHint());
            controller->_inputEvaluator = PointValidator::createInstance(details->terminalKeyCode());
            controller->_indexService = PointIndexController::createInstance(details->attempts());
            controller->_inputService = DartsPlayerPointService::createInstance(details->keyPoint(),details->winnerId());
            controller->_dartsJsonService = new DartsPointJsonService;
            controller->_turnValuesBuilder = new BuildDartsPointTurnValues;
            controller->_pointModelBuilder = new DartsPointBuilderService;
            controller->_dartsIndexesBuilderService = new DartsIndexesBuilderService;
            controller->_controllerModelsService = new DartsControllerPointModelsService;
            controller->_playerModelBuilder = new DartsPlayerModelBuilderService;
            controller->_getOrderedDartsPointsByJson = new GetOrderedDartsPointsByJson;
            controller->_addTotalScoresToDartsModelsJson = new AddTotalScoreToDartsInputsJson;
            controller->_dartsPointsToJson = new DartsPointInputsToJson;
            controller->_calculateScoreByPointInput = new CalculateScoreByDartsPointInput;
            controller->_combineJsonService = new JsonMergeByByteArrayService;
            controller->_addPlayerNamesToDartsModelsJson = new AddPlayerNamestoDartsPointsJson;
            controller->_addTotalScoreToPointModel = new AddTotalScoreToDartsPoint;
            return controller;
        }
    private:
        DefaultDartsPointController(const QUuid &tournament, const int &displayHint) :
            DartsPointController(tournament,displayHint)
        {}
    };
}

#endif // DEFAULTDARTSPOINTCONTROLLER_H
