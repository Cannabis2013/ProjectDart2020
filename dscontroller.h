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
#include <dcwinnerkeys.h>
#include <dccreateplayersfromjson.h>
#include <dcplayerkeys.h>
#include "dscinputsuggestion.h"
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
#include "dscinputsuggestion.h"
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
#include "dcgetwinnermodelfromjson.h"
class DSController : public DartsController
{
public:
    DSController(const DCBuilding::IDCMetaInfo *meta)
    {
        setScoreLogisticInterface(new DSCInputSuggestion);
        setInputEvaluator(new ScoreValidator(meta));
        setIndexService(new DCIndexController(meta));
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
        setCreateScoreTuples(new DCCreateScoreTuples);
        setTurnValuesToJsonService(new DCTurnValuesToJson);
        setResponseBuilderService(new DCJsonResponseBuilder);
        // Json services
        setJsonExtractor(new JsonValuesExtractor);
        // Input services
        setGetScoreFromInput(new GetScoreFromDSCInput);
        // Player score services
        setSubtractScore(new DCSubtractScore);
        setReplaceTuples(new DCUpdateTuples);
        // Player services
        setPlayerService(new DCPlayerService(indexService(),scoresService()));
        setGetPlayerName(new DCGetPlayerName);
        setWinnerModelFromJson(new DCGetWInnerModelsFromJson);
        setCreateJsonFromPlayer(new CreateJsonFromDCPlayer);
        setCreatePlayersFromJson(new DCCreatePlayersFromJson);
        setWinnerKeys(new DCWinnerKeys);
        setPlayerKeys(new DCPlayerKeys);
        // Index services
        setInitializeIndexes(new DCInitializeIndexes);
        setIndexIterator(new DCIndexIterator);
        setResetIndexes(new DCResetIndexes);
        setUndoIndex(new DCIndexUndo);
        setRedoIndex(new DCIndexRedo);
        setIndexesToJsonService(new DSCIndexesToJson);
    }
};
#endif // DEFAULTDARTSSCORECONTROLLER_H
