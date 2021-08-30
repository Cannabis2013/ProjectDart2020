#ifndef DEFAULTDSCONTROLLER_H
#define DEFAULTDSCONTROLLER_H

#include "dscontroller.h"
#include "idcmetainfo.h"
#include <quuid.h>
#include "dartssingleattemptinputrowsuggestion.h"
#include "ScoreValidator.h"
#include "dcwinnerservice.h"
#include "createjsonfromdscmodels.h"
#include "dartsscoremodelsbuilder.h"
#include "dsindexesbuilder.h"
#include "scoreindexcontroller.h"
#include "determinecontrollerstatebywinnerid.h"
#include "dscvaluesbuilder.h"
#include "GenereicJsonBuilder.h"
#include "dartsplayerbuilderservice.h"
#include "jsonmergebybytearrayservice.h"
#include "mhjsonextractor.h"
#include "dartssingleattemptinputrowsuggestion.h"
#include "dartsmetadataservice.h"
#include "dcscoresservice.h"
#include "dartssubtractscores.h"
#include "dartsaddscore.h"
#include "dsccalccandidate.h"

class DefaultDSController : public DSController
{
public:
    DefaultDSController(const DartsBuilderContext::IDCMetaInfo *details)
    {
        _scoreLogisticInterface = DartsSingleAttemptInputRowSuggestion::createInstance();
        _inputEvaluator = ScoreValidator::createInstance(details->terminalKeyCode());
        _indexService = DSCContext::ScoreIndexController::createInstance();
        _winnerService = new DCWinnerService();
        _turnValuesBuilder = new DSCContext::DSCValuesBuilder;
        _dartsScoreBuilder = new DSCContext::DartsScoreModelsBuilder;
        _dartsIndexesBuilderService = new DSCContext::DSIndexesBuilder;
        _playerBuilderService = new DSCContext::DartsPlayerBuilderService;
        _metaData = DartsMetaDataService::createInstance(details->tournamentId(),details->displayHint());
        _determineControllerStateByWinnerId = new DartsControllerContext::DetermineControllerStateByWinnerId;
        setJsonModelBuilderService(new DSCContext::CreateJsonFromDSCModels);
        setScoresService(new DCScoresService);
        setJsonMerger(new JsonMergeByByteArrayService);
        setJsonBuilderService(new GenericJsonBuilder);
        setExtractJsonService(new MHJsonExtractor);
        setSubtractService(new DartsSubtractScores);
        setAddScoreService(new DartsAddScore);
        setCalcAccScoreCand(new DSCCalcCandidate);
    }
};

#endif // DEFAULTDARTSSCORECONTROLLER_H
