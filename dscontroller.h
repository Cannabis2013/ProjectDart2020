#ifndef DSCONTROLLER_H
#define DSCONTROLLER_H
#include "dartscontroller.h"
#include "idcmetainfo.h"
#include <createjsonfromdcplayer.h>
#include <dccreatescoretuples.h>
#include <dcindexesbuilder.h>
#include <dcindexredo.h>
#include <dcplayerservice.h>
#include <dcresetindexes.h>
#include <dcsubtractscore.h>
#include <dcturnvaluestojson.h>
#include <dcindexundo.h>
#include <jsonvaluesextractor.h>
#include <quuid.h>
#include <dcgetplayername.h>
#include "dartssingleattemptinputrowsuggestion.h"
#include "ScoreValidator.h"
#include "dcwinnerservice.h"
#include "dscinputtojson.h"
#include "dsccreateinputmodels.h"
#include "dcindexcontroller.h"
#include "determinecontrollerstatebywinnerid.h"
#include "dscvaluesbuilder.h"
#include "genericjsonbuilder.h"
#include "dcplayerbuilder.h"
#include "jsonmerger.h"
#include "dartssingleattemptinputrowsuggestion.h"
#include "dartsmetadataservice.h"
#include "dcscoresservice.h"
#include "dcupdatetuples.h"
#include "dccreatecandidatetuples.h"
#include "dcaddscore.h"
#include "dcgetscorecand.h"
#include "dcinitializeindexservice.h"
#include "getscorefromdscinput.h"
#include "dscindexestojson.h"
#include "dcjsonresponsebuilder.h"
#include "dcindexiterator.h"
class DSController : public DartsController
{
public:
    DSController(const DartsBuilderContext::IDCMetaInfo *meta)
    {
        setScoreLogisticInterface(DartsSingleAttemptInputRowSuggestion::createInstance());
        setInputEvaluator(ScoreValidator::createInstance(meta->terminalKeyCode()));
        setIndexService(new DCIndexController(meta->attempts()));
        setWinnerService(new DCWinnerService());
        setTurnValuesBuilder(new DSCContext::DSCValuesBuilder);
        setInputModelBuilder(new DSCCreateInputModels);
        setIndexesBuilder(new DCIndexesBuilder);
        setCreateCandidateTuples(new DCCreateCandidateTuples);
        setPlayerBuilderService(new DCPlayerBuilder);
        setMetaData(new DCMetaInfo(meta));
        setDetermineControllerStateByWinnerId(new DetermineControllerStateByWinnerId);
        setInputsToJsonService(new DSCInputToJson);
        setScoresService(new DCScoresService);
        setAddScoreService(new DCAddScore);
        setGetTotalScoreService(new DCGetScoreCand);
        setReplaceTuples(new DCUpdateTuples);
        setInitializeIndexes(new DCInitializeIndexes);
        setCreateScoreTuples(new DCCreateScoreTuples);
        setTurnValuesToJsonService(new DCTurnValuesToJson);
        setGetScoreFromInput(new GetScoreFromDSCInput);
        setIndexesToJsonService(new DSCIndexesToJson);
        setCreateJsonFromPlayer(new CreateJsonFromDCPlayer);
        setResponseBuilderService(new DCJsonResponseBuilder);
        setJsonExtractor(new JsonValuesExtractor);
        // Player score services
        setSubtractScore(new DCSubtractScore);
        // Player services
        setPlayerService(new DCPlayerService(indexService(),scoresService()));
        setGetPlayerName(new DCGetPlayerName);
        // Index services
        setIndexIterator(new DCIndexIterator);
        setResetIndexes(new DCResetIndexes);
        setUndoIndex(new DCIndexUndo);
        setRedoIndex(new DCIndexRedo);
    }
};
#endif // DEFAULTDARTSSCORECONTROLLER_H
