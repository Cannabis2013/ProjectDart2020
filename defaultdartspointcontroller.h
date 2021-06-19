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
#include "addtotalscoretodartsinputs.h"
#include "dartspointinputstojson.h"
#include "CombineDartsIndexesAndDartsPointJson.h"

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
            controller->_indexController = PointIndexController::createInstance(details->attempts());
            controller->_playerPointsService = DartsPlayerPointService::createInstance(details->keyPoint(),details->winnerId());
            controller->_dartsJsonService = new DartsPointJsonService;
            controller->_dartsTurnValuesBuilderService = new BuildDartsPointTurnValues;
            controller->_pointModelBuilderService = new DartsPointBuilderService;
            controller->_dartsIndexesBuilderService = new DartsIndexesBuilderService;
            controller->_controllerModelsService = new DartsControllerPointModelsService;
            controller->_playerModelBuilderService = new DartsPlayerModelBuilderService;
            controller->_getOrderedDartsPointsByJson = new GetOrderedDartsPointsByJson;
            controller->_addTotalScoresServices = new AddTotalScoreToDartsInputs;
            controller->_dartsPointsToJson = new DartsPointInputsToJson;
            controller->_calculateScoreByPointInput = new CalculateScoreByDartsPointInput;
            controller->_combineDartsIndexesAndDartsPoint = new CombineDartsIndexesAndDartsPointJson;
            return controller;
        }
    private:
        DefaultDartsPointController(const QUuid &tournament, const int &displayHint) :
            DartsPointController(tournament,displayHint)
        {}
    };
}

#endif // DEFAULTDARTSPOINTCONTROLLER_H
