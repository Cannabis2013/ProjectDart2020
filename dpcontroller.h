#ifndef DPCONTROLLER_H
#define DPCONTROLLER_H

#include "idcmetainfo.h"

#include "GetScoreFromDCPointModel.h"
#include "pointvalidator.h"
#include "CreateDPCTurnValues.h"
#include "dpccreateinputmodels.h"
#include "dcindexesbuilder.h"
#include "dartsplayermodelbuilderservice.h"
#include "dartscontrollerpointmodelsservice.h"
#include "addtotalscoretodartspointsjson.h"
#include "addplayernamestodartspointsjson.h"
#include "jsonmerger.h"
#include "GenereicJsonBuilder.h"
#include "dartsmetadataservice.h"
#include "dartspointstringsuggestion.h"
#include "determinecontrollerstatebywinnerid.h"
#include "dpcpointtojson.h"
#include "dcscoresservice.h"
#include "dccreatecandidatetuples.h"
#include "dcinitializeindexservice.h"

#include <dcwinnerservice.h>
#include <dartscontroller.h>
#include <pointvalidator.h>
#include <dcindexcontroller.h>
#include <dcplayerbuilder.h>
#include <dartsaddscore.h>

namespace DartsBuilderContext {
    class DPController : public DartsController
    {
    public:
        DPController(const IDCMetaInfo *details)
        {
            _inputEvaluator = PointValidator::createInstance(details->terminalKeyCode());
            _indexService = new DCIndexController;
            setInitializeIndexes(new DCInitializeIndexes);
            setTurnValuesBuilder(new CreateDPCTurnValues);
            setInputModelBuilder(new DPCCreateInputModels);
            setIndexesBuilder(new DCIndexesBuilder);
            setPlayerBuilderService(new DCPlayerBuilder);
            setCalculateScore(new GetScoreFromDCPointModel);
            setAddScoreService(new DartsAddScore);
            setAddTotalScoresToJson(new AddTotalScoreToDartsPointsJson);
            setAddPlayerNamesToJson(new AddPlayerNamestoDartsPointsJson);
            setJsonGenericBuilder(new GenericJsonBuilder);
            _metaData = new DartsMetaDataService(details->tournamentId(),details->displayHint(),details->keyPoint());
            _scoreLogisticInterface = DartsPointStringSuggestion::createInstance(details->attempts());
            setDetermineControllerStateByWinnerId(new DetermineControllerStateByWinnerId);
            //setCreateJsonFromPoint(new DPCPointToJson);
            setScoresService(new DCScoresService);
            setCreateCandidateTuples(new DCCreateCandidateTuples);
            setWinnerService(new DCWinnerService);
        }

    };
}
#endif // DEFAULTDARTSPOINTCONTROLLER_H
