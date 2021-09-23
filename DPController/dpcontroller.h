#ifndef DPCONTROLLER_H
#define DPCONTROLLER_H
#include "idcmetainfo.h"
#include "DCIndexServices/dcindexesbuilder.h"
#include "dartscontrollerpointmodelsservice.h"
#include "DCJsonServices/addtotalscoretodartsinputsasjson.h"
#include "DCJsonServices/addplayernamestodartsinputsasjson.h"
#include "jsonmerger.h"
#include "genericjsonbuilder.h"
#include "DCFinishesServices/dcinputfinishes.h"
#include "DCMetaServices/determinestatusbyid.h"
#include "DCScoresServices/dcscoresservice.h"
#include "dccreatecandidatemodels.h"
#include "DCIndexServices/dcinitializeindexservice.h"
#include "DCMetaServices/dcwinnerservice.h"
#include "DartsController/dartscontroller.h"
#include "DCPlayerServices/dcplayerbuilder.h"
#include "DCPlayerServices/dcplayerservice.h"
#include "DCScoresServices/dcaddscore.h"
#include "DCScoresServices/dccreatescoremodels.h"
#include "DCScoresServices/dcupdatescoremodels.h"
#include "DCTurnValuesServices/dcturnvaluestojson.h"
#include "DCScoresServices/dcgetscorecand.h"
#include <dcjsonresponsebuilder.h>
#include "DCIndexServices/dcindexiterator.h"
#include "DCIndexServices/dcindexredo.h"
#include "DCPlayerServices/dcwinnerkeys.h"
#include "jsonvaluesextractor.h"
#include "DCScoresServices/dcsubtractscore.h"
#include "DCIndexServices/dcresetindexes.h"
#include "DCIndexServices/dcindexundo.h"
#include "DCPlayerServices/dcgetplayername.h"
#include "DCPlayerServices/dcgetwinnermodelfromjson.h"
#include "DCPlayerServices/dccreateplayersfromjson.h"
#include "DCPlayerServices/dcplayerkeys.h"
#include "DCFinishesServices/dccreatefinishes.h"
#include "DCFinishesServices/dclogisticdb.h"
#include "DCScoresServices/dcresetscoremodels.h"
#include "DCMetaServices/dcmetastatus.h"
#include "DCMetaServices//dartsstatuscodes.h"
#include "DCInputServices/dccreateinputmodels.h"
#include "DCMetaServices/dchint.h"
#include "DCMetaServices/dcinitialscore.h"
#include "DCMetaServices/dctournamentid.h"
#include "DPCServices/dpcinputvalidator.h"
#include "DPCServices/dpcindexcontroller.h"
#include "DPCServices/CreateDPCTurnValues.h"
#include "DPCServices/dpccreateinputmodel.h"
#include "DPCServices/getscorefromdpcinput.h"
#include "DPCServices/dpcinputstojson.h"
#include "DPCServices/dpcinputstojson.h"
#include "DPCServices/dpcindexestojson.h"
#include "DCInputServices/dcinputjsonkeys.h"

class DPController : public DartsController
{
public:
    DPController(const DCBuilding::IDCMetaInfo *meta)
    {
        setInputEvaluator(DPCInputValidator::createInstance());
        setIndexService(new DPCIndexController);
        setTurnValuesBuilder(new CreateDPCTurnValues);
        setCreateInputModelService(new DPCCreateInputModel);
        setIndexesBuilder(new DCIndexesBuilder);
        setGetScoreFromInput(new GetScoreFromDPCInput);
        setAddScoreService(new DCAddScore);
        setAddTotalScoresToJson(new AddTotalScoreToDartsInputsAsJson);
        setAddPlayerNamesToJson(new AddPlayerNamestoDartsInputsAsJson);
        setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(), DCLogisticDb::createInstance()));
        setDetermineStatusById(new DetermineStatusById);
        setGetTotalScoreService(new DCGetScoreCand);
        // Meta services
        setMetaStatus(new DCMetaStatus);
        setStatusCodes(new DCStatusCodes);
        setDisplayHint(DCHint::createInstance(meta->displayHint()));
        setInputHint(DCHint::createInstance(meta->inputHint()));
        setTournamentId(DCTournamentId::createInstance(meta->tournamentId()));
        setInitialScore(DCInitialScore::createInstance(meta->keyPoint()));
        // Json services
        setInputsToJsonService(new DPCInputsToJson);
        setTurnValuesToJsonService(new DCTurnValuesToJson);
        setResponseBuilderService(new DCJsonResponseBuilder);
        setIndexesToJsonService(new DPCIndexesToJson);
        // Score tuple services
        setResetScoreModels(new DCResetScoreModels);
        setCreateScoreModelsService(new DCCreateScoreModels);
        setUpdateScoreModels(new DCUpdateScoreModels);
        setSubtractScore(new DCSubtractScore);
        setScoresService(new DCScoresService);
        setCreateCandidateTuples(new DCCreateCandidateModels);
        setWinnerService(new DCWinnerService);
        setJsonExtractor(new JsonValuesExtractor);
        // Input services
        setCreateInputModels(new DCCreateInputModels);
        setInputKeys(new DCInputJsonKeys);
        // Player services
        setPlayerBuilderService(new DCPlayerBuilder);
        setPlayerService(new DCPlayerService(indexService(),scoresService()));
        setGetPlayerName(new DCGetPlayerName);
        setWinnerModelFromJson(new DCGetWInnerModelsFromJson);
        setCreatePlayersFromJson(new DCCreatePlayersFromJson);
        setWinnerKeys(new DCWinnerKeys);
        setPlayerKeys(new DCPlayerKeys);
        // Index services
        setResetIndexes(new DCResetIndexes);
        setInitializeIndexes(new DCInitializeIndexes);
        setIndexIterator(new DCIndexIterator);
        setUndoIndex(new DCIndexUndo);
        setRedoIndex(new DCIndexRedo);
    }
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
