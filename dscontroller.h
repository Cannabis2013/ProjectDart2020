#ifndef DSCONTROLLER_H
#define DSCONTROLLER_H
#include "DartsController/Controller/dartscontroller.h"
#include "idcmetainfo.h"
#include "DartsController/DCPlayerServices/createjsonfromdcplayer.h"
#include "DartsController/DCScoresServices/dccreatescoremodels.h"
#include "DartsController/DCIndexServices/dcindexesbuilder.h"
#include "DartsController/DCIndexServices/dcindexredo.h"
#include "DartsController/DCPlayerServices/dcplayerservice.h"
#include "DartsController/DCIndexServices/dcresetindexes.h"
#include "DartsController/DCScoresServices/dcsubtractscore.h"
#include "DartsController/DCTurnValuesServices/dcturnvaluestojson.h"
#include "DartsController/DCIndexServices/dcindexundo.h"
#include <jsonvaluesextractor.h>
#include <quuid.h>
#include "DartsController/DCPlayerServices/dcgetplayername.h"
#include "DartsController/DCPlayerServices/dcwinnerkeys.h"
#include "DartsController/DCPlayerServices/dccreateplayersfromjson.h"
#include "DartsController/DCPlayerServices/dcplayerkeys.h"
#include "DartsController/DSCServices/dscindexcontroller.h"
#include "DartsController/DSCServices/dscinputsuggestion.h"
#include "DartsController/DSCServices/dscinputvalidator.h"
#include "DartsController/DCMetaServices/dcwinnerservice.h"
#include "DartsController/DSCServices/dscinputtojson.h"
#include "DartsController/DSCServices/dsccreateinputmodel.h"
#include "DartsController/DCMetaServices/determinestatusbyid.h"
#include "DartsController/DSCServices/dscvaluesbuilder.h"
#include "genericjsonbuilder.h"
#include "DartsController/DCPlayerServices/dcplayerbuilder.h"
#include "jsonmerger.h"
#include "DartsController/DSCServices/dscinputsuggestion.h"
#include "DartsController/DCScoresServices/dcscoresservice.h"
#include "DartsController/DCScoresServices/dcupdatescoremodels.h"
#include "dccreatecandidatemodels.h"
#include "DartsController/DCScoresServices/dcaddscore.h"
#include "DartsController/DCScoresServices/dcgetscorecand.h"
#include "DartsController/DCIndexServices/dcinitializeindexservice.h"
#include "DartsController/DSCServices/getscorefromdscinput.h"
#include "DartsController/DSCServices/dscindexestojson.h"
#include "dcjsonresponsebuilder.h"
#include "DartsController/DCIndexServices/dcindexiterator.h"
#include "DartsController/DCPlayerServices/dcgetwinnermodelfromjson.h"
#include "DartsController/DCScoresServices/dcresetscoremodels.h"
#include "DartsController/DCFinishesServices/dccreatefinishes.h"
#include "DartsController/DCFinishesServices/dclogisticdb.h"
#include "DartsController/DCFinishesServices/dcinputfinishes.h"
#include "DartsController/DCMetaServices//dartsstatuscodes.h"
#include "DartsController/DCMetaServices/dcmetastatus.h"
#include "DartsController/DCMetaServices/dchint.h"
#include "DartsController/DCMetaServices/dcinitialscore.h"
#include "DartsController/DCMetaServices/dctournamentid.h"
#include "DartsController/DCInputServices/dccreateinputmodels.h"
#include "DartsController/DCInputServices/dcinputjsonkeys.h"
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
