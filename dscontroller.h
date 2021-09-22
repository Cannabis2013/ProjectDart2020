#ifndef DSCONTROLLER_H
#define DSCONTROLLER_H
#include "DartsController/dartscontroller.h"
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
#include <dscindexcontroller.h>
#include "dscinputsuggestion.h"
#include "dscinputvalidator.h"
#include "dcwinnerservice.h"
#include "dscinputtojson.h"
#include "dsccreateinputmodel.h"
#include "determinestatusbyid.h"
#include "dscvaluesbuilder.h"
#include "genericjsonbuilder.h"
#include "dcplayerbuilder.h"
#include "jsonmerger.h"
#include "dscinputsuggestion.h"
#include "dcscoresservice.h"
#include "dcupdatescoremodels.h"
#include "dccreatecandidatetuples.h"
#include "dcaddscore.h"
#include "dcgetscorecand.h"
#include "dcinitializeindexservice.h"
#include "getscorefromdscinput.h"
#include "dscindexestojson.h"
#include "dcjsonresponsebuilder.h"
#include "dcindexiterator.h"
#include "dcgetwinnermodelfromjson.h"
#include "dcresetscoremodels.h"
#include "dccreatefinishes.h"
#include "dclogisticdb.h"
#include "dcinputfinishes.h"
#include "DartsController/dartsstatuscodes.h"
#include "DartsController/dcmetastatus.h"
#include "DartsController/dchint.h"
#include "DartsController/dcinitialscore.h"
#include "DartsController/dctournamentid.h"
#include "DartsController/dccreateinputmodels.h"
class DSController : public DartsController
{
public:
    DSController(const DCBuilding::IDCMetaInfo *meta)
    {
        setInputEvaluator(new DSCInputValidator);
        setIndexService(new DSCIndexController);
        setWinnerService(new DCWinnerService());
        setTurnValuesBuilder(new DSCContext::DSCValuesBuilder);
        setCreateInputModelService(new DSCCreateInputModel);
        setIndexesBuilder(new DCIndexesBuilder);
        setCreateCandidateTuples(new DCCreateCandidateTuples);
        setPlayerBuilderService(new DCPlayerBuilder);
        setDetermineStatusById(new DetermineStatusById);
        setInputsToJsonService(new DSCInputToJson);
        setScoresService(new DCScoresService);
        setAddScoreService(new DCAddScore);
        setGetTotalScoreService(new DCGetScoreCand);
        setCreateScoreTuples(new DCCreateScoreTuples);
        setTurnValuesToJsonService(new DCTurnValuesToJson);
        setResponseBuilderService(new DCJsonResponseBuilder);
        setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(), DCLogisticDb::createInstance()));
        // Meta services
        setMetaStatus(new DCMetaStatus);
        setStatusCodes(new DCStatusCodes);
        setDisplayHint(DCHint::createInstance(meta->displayHint()));
        setInputHint(DCHint::createInstance(meta->inputHint()));
        setTournamentId(DCTournamentId::createInstance(meta->tournamentId()));
        setInitialScore(DCInitialScore::createInstance(meta->keyPoint()));
        // Json services
        setJsonExtractor(new JsonValuesExtractor);
        // Input services
        setGetScoreFromInput(new GetScoreFromDSCInput);
        setCreateInputModels(new DCCreateInputModels);
        // Player score services
        setSubtractScore(new DCSubtractScore);
        setReplaceScoreModels(new DCUpdateScoreModels);
        setResetScoreModels(new DCResetScoreModels);
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
