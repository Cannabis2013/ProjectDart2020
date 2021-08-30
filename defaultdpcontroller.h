#ifndef DEFAULTDPCONTROLLER_H
#define DEFAULTDPCONTROLLER_H

#include "dpcontroller.h"
#include "idcmetainfo.h"

#include "CalculateScoreByDartsPointInput.h"
#include "pointvalidator.h"
#include "PointIndexController.h"
#include "CreateDPCTurnValues.h"
#include "dpcmodelcreator.h"
#include "DPIndexesBuilder.h"
#include "dartsplayermodelbuilderservice.h"
#include "dartscontrollerpointmodelsservice.h"
#include "addtotalscoretodartspointsjson.h"
#include "addplayernamestodartspointsjson.h"
#include "jsonmergebybytearrayservice.h"
#include "addtotalscoretodartspoint.h"
#include "GenereicJsonBuilder.h"
#include "mhjsonextractor.h"
#include "dartsmetadataservice.h"
#include "dartspointstringsuggestion.h"
#include "determinecontrollerstatebywinnerid.h"
#include "createjsonfromdpcpoint.h"
#include "dcscoresservice.h"
#include "dpcsubtractplayerscore.h"

#include <dcwinnerservice.h>

namespace DartsBuilderContext {
    class DefaultDPController : public DPCContext::DPController
    {
    public:
        DefaultDPController(IDCMetaInfo *details)
        {
            _inputEvaluator = PointValidator::createInstance(details->terminalKeyCode());
            _indexService = DPCContext::PointIndexController::createInstance(details->attempts());
            _turnValuesBuilder = new DPCContext::CreateDPCTurnValues;
            _pointModelBuilder = new DPCModelCreator;
            _dartsIndexesBuilder = new DPCContext::DPIndexesBuilder;
            _controllerModels = new DPCContext::DartsControllerPointModelsService;
            _playerModelBuilder = new DPCContext::DartsPlayerModelBuilderService;
            _calculateScoreByPointInput = new DPCContext::CalculateScoreByDartsPointInput;
            _addTotalScoreToPointModel = new DPCContext::AddTotalScoreToDartsPoint;
            setAddTotalScoresToDartsModelsJson(new DPCContext::AddTotalScoreToDartsPointsJson);
            setAddPlayerNamesToDartsModelsJson(new AddPlayerNamestoDartsPointsJson);
            setJsonMerger(new JsonMergeByByteArrayService);
            setJsonBuilder(new GenericJsonBuilder);
            setJsonExtractor(new MHJsonExtractor);
            _metaData = DartsMetaDataService::createInstance(details->tournamentId(),details->displayHint());
            _stringSuggestionService = DartsPointStringSuggestion::createInstance(details->attempts());
            _determineControllerStateByWinnerId = new DartsControllerContext::DetermineControllerStateByWinnerId;
            setCreateJsonFromPoint(new CreateJsonFromDPCPoint);
            setScoresService(new DCScoresService);
            setSubTractScore(new DPCSubtractScore);
            setWinnerService(new DCWinnerService);
        }

    };
}

#endif // DEFAULTDARTSPOINTCONTROLLER_H
