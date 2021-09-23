#ifndef DPCONTROLLER_H
#define DPCONTROLLER_H
#include "idcmetainfo.h"
#include "DartsController/DCIndexServices/dcindexesbuilder.h"
#include "dartscontrollerpointmodelsservice.h"
#include "DartsController/DCJsonServices/addtotalscoretodartsinputsasjson.h"
#include "DartsController/DCJsonServices/addplayernamestodartsinputsasjson.h"
#include "jsonmerger.h"
#include "genericjsonbuilder.h"
#include "DartsController/DCFinishesServices/dcinputfinishes.h"
#include "DartsController/DCMetaServices/determinestatusbyid.h"
#include "DartsController/DCScoresServices/dcscoresservice.h"
#include "dccreatecandidatemodels.h"
#include "DartsController/DCIndexServices/dcinitializeindexservice.h"
#include "DartsController/DCMetaServices/dcwinnerservice.h"
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DCPlayerServices/dcplayerbuilder.h"
#include "DartsController/DCPlayerServices/dcplayerservice.h"
#include "DartsController/DCScoresServices/dcaddscore.h"
#include "DartsController/DCScoresServices/dccreatescoremodels.h"
#include "DartsController/DCScoresServices/dcupdatescoremodels.h"
#include "DartsController/DCTurnValuesServices/dcturnvaluestojson.h"
#include "DartsController/DCScoresServices/dcgetscorecand.h"
#include <dcjsonresponsebuilder.h>
#include "DartsController/DCIndexServices/dcindexiterator.h"
#include "DartsController/DCIndexServices/dcindexredo.h"
#include "DartsController/DCPlayerServices/dcwinnerkeys.h"
#include "jsonvaluesextractor.h"
#include "DartsController/DCScoresServices/dcsubtractscore.h"
#include "DartsController/DCIndexServices/dcresetindexes.h"
#include "DartsController/DCIndexServices/dcindexundo.h"
#include "DartsController/DCPlayerServices/dcgetplayername.h"
#include "DartsController/DCPlayerServices/dcgetwinnermodelfromjson.h"
#include "DartsController/DCPlayerServices/dccreateplayersfromjson.h"
#include "DartsController/DCPlayerServices/dcplayerkeys.h"
#include "DartsController/DCFinishesServices/dccreatefinishes.h"
#include "DartsController/DCFinishesServices/dclogisticdb.h"
#include "DartsController/DCScoresServices/dcresetscoremodels.h"
#include "DartsController/DCMetaServices/dcmetastatus.h"
#include "DartsController/DCMetaServices//dartsstatuscodes.h"
#include "DartsController/DCInputServices/dccreateinputmodels.h"
#include "DartsController/DCMetaServices/dchint.h"
#include "DartsController/DCMetaServices/dcinitialscore.h"
#include "DartsController/DCMetaServices/dctournamentid.h"
#include "DartsController/DPCServices/dpcinputvalidator.h"
#include "DartsController/DPCServices/dpcindexcontroller.h"
#include "DartsController/DPCServices/CreateDPCTurnValues.h"
#include "DartsController/DPCServices/dpccreateinputmodel.h"
#include "DartsController/DPCServices/getscorefromdpcinput.h"
#include "DartsController/DPCServices/dpcinputstojson.h"
#include "DartsController/DPCServices/dpcinputstojson.h"
#include "DartsController/DPCServices/dpcindexestojson.h"
#include "DartsController/DCInputServices/dcinputjsonkeys.h"

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
