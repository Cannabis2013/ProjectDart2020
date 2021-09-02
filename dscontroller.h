#ifndef DSCONTROLLER_H
#define DSCONTROLLER_H

#include "dartscontroller.h"
#include "idcmetainfo.h"
#include <dccreatescoretuples.h>
#include <dcindexesbuilder.h>
#include <quuid.h>
#include "dartssingleattemptinputrowsuggestion.h"
#include "ScoreValidator.h"
#include "dcwinnerservice.h"
#include "createjsonfromdscmodels.h"
#include "dsccreateinputmodels.h"
#include "dcindexcontroller.h"
#include "determinecontrollerstatebywinnerid.h"
#include "dscvaluesbuilder.h"
#include "GenereicJsonBuilder.h"
#include "dcplayerbuilder.h"
#include "jsonmerger.h"
#include "dartssingleattemptinputrowsuggestion.h"
#include "dartsmetadataservice.h"
#include "dcscoresservice.h"
#include "dcreplacetuples.h"
#include "dccreatecandidatetuples.h"
#include "dartsaddscore.h"
#include "dsccalccandidate.h"
#include "dcinitializeindexservice.h"

class DSController : public DartsController
{
public:
    DSController(const DartsBuilderContext::IDCMetaInfo *details)
    {
        _scoreLogisticInterface = DartsSingleAttemptInputRowSuggestion::createInstance();
        _inputEvaluator = ScoreValidator::createInstance(details->terminalKeyCode());
        _indexService = new DCIndexController();
        _winnerService = new DCWinnerService();
        setTurnValuesBuilder(new DSCContext::DSCValuesBuilder);
        setInputModelBuilder(new DSCCreateInputModels);
        setIndexesBuilder(new DCIndexesBuilder);
        setCreateCandidateTuples(new DCCreateCandidateTuples);
        setPlayerBuilderService(new DCPlayerBuilder);
        _metaData = new DartsMetaDataService(details->tournamentId(),details->displayHint(),details->keyPoint());
        setDetermineControllerStateByWinnerId(new DetermineControllerStateByWinnerId);
        setJsonModelBuilderService(new CreateJsonFromDSCModels);
        setScoresService(new DCScoresService);
        setJsonGenericBuilder(new GenericJsonBuilder);
        setAddScoreService(new DartsAddScore);
        setCalcAccScoreCand(new DSCCalcCandidate);
        setReplaceTuples(new DCReplaceTuples);
        setInitializeIndexes(new DCInitializeIndexes);
        setCreateScoreTuples(new DCCreateScoreTuples);
    }
};

#endif // DEFAULTDARTSSCORECONTROLLER_H
