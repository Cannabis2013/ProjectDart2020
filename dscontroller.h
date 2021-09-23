#ifndef DSCONTROLLER_H
#define DSCONTROLLER_H
#include "DartsController/dartscontroller.h"
#include "idcmetainfo.h"
#include "DCPlayerServices/createjsonfromdcplayer.h"
#include "DCScoresServices/dccreatescoremodels.h"
#include "DCIndexServices/dcindexesbuilder.h"
#include "DCIndexServices/dcindexredo.h"
#include "DCPlayerServices/dcplayerservice.h"
#include "DCIndexServices/dcresetindexes.h"
#include "DCScoresServices/dcsubtractscore.h"
#include "DCTurnValuesServices/dcturnvaluestojson.h"
#include "DCIndexServices/dcindexundo.h"
#include <jsonvaluesextractor.h>
#include <quuid.h>
#include "DCPlayerServices/dcgetplayername.h"
#include "DCPlayerServices/dcwinnerkeys.h"
#include "DCPlayerServices/dccreateplayersfromjson.h"
#include "DCPlayerServices/dcplayerkeys.h"
#include "DSCServices/dscindexcontroller.h"
#include "DSCServices/dscinputsuggestion.h"
#include "DSCServices/dscinputvalidator.h"
#include "DCMetaServices/dcwinnerservice.h"
#include "DSCServices/dscinputtojson.h"
#include "DSCServices/dsccreateinputmodel.h"
#include "DCMetaServices/determinestatusbyid.h"
#include "DSCServices/dscvaluesbuilder.h"
#include "genericjsonbuilder.h"
#include "DCPlayerServices/dcplayerbuilder.h"
#include "jsonmerger.h"
#include "DSCServices/dscinputsuggestion.h"
#include "DCScoresServices/dcscoresservice.h"
#include "DCScoresServices/dcupdatescoremodels.h"
#include "dccreatecandidatemodels.h"
#include "DCScoresServices/dcaddscore.h"
#include "DCScoresServices/dcgetscorecand.h"
#include "DCIndexServices/dcinitializeindexservice.h"
#include "DSCServices/getscorefromdscinput.h"
#include "DSCServices/dscindexestojson.h"
#include "dcjsonresponsebuilder.h"
#include "DCIndexServices/dcindexiterator.h"
#include "DCPlayerServices/dcgetwinnermodelfromjson.h"
#include "DCScoresServices/dcresetscoremodels.h"
#include "DCFinishesServices/dccreatefinishes.h"
#include "DCFinishesServices/dclogisticdb.h"
#include "DCFinishesServices/dcinputfinishes.h"
#include "DCMetaServices//dartsstatuscodes.h"
#include "DCMetaServices/dcmetastatus.h"
#include "DCMetaServices/dchint.h"
#include "DCMetaServices/dcinitialscore.h"
#include "DCMetaServices/dctournamentid.h"
#include "DCInputServices/dccreateinputmodels.h"
#include "DCInputServices/dcinputjsonkeys.h"
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
        setCreateCandidateTuples(new DCCreateCandidateModels);
        setPlayerBuilderService(new DCPlayerBuilder);
        setDetermineStatusById(new DetermineStatusById);
        setScoresService(new DCScoresService);
        setAddScoreService(new DCAddScore);
        setGetTotalScoreService(new DCGetScoreCand);
        setCreateScoreModelsService(new DCCreateScoreModels);
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
        setInputsToJsonService(new DSCInputToJson);
        setGetScoreFromInput(new GetScoreFromDSCInput);
        setCreateInputModels(new DCCreateInputModels);
        setInputKeys(new DCInputJsonKeys);
        // Player score services
        setSubtractScore(new DCSubtractScore);
        setUpdateScoreModels(new DCUpdateScoreModels);
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
