#ifndef DPCONTROLLER_H
#define DPCONTROLLER_H
#include "DartsControllerBuilder/DCBMetaSLAs/idcmetainfo.h"
#include "DartsController/DCIndexServices/dcindexesbuilder.h"
#include "DartsController/DCJsonServices/addtotalscoretodartsinputsasjson.h"
#include "DartsController/DCJsonServices/addplayernamestodartsinputsasjson.h"
#include "DartsController/DCFinishesServices/dcinputfinishes.h"
#include "DartsController/DCMetaServices/determinestatusbyid.h"
#include "DartsController/DCScoresServices/dcscoresservice.h"
#include "DartsController/DCScoresServices/dccreatecandidatemodels.h"
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
#include "DartsController/DCIndexServices/dcindexiterator.h"
#include "DartsController/DCIndexServices/dcindexredo.h"
#include "DartsController/DCPlayerServices/dcwinnerkeys.h"
#include "DartsController/DCScoresServices/dcsubtractscore.h"
#include "DartsController/DCIndexServices/dcresetindexes.h"
#include "DartsController/DCIndexServices/dcindexundo.h"
#include "DartsController/DCPlayerServices/dcgetwinnermodelfromjson.h"
#include "DartsController/DCPlayerServices/dccreateplayersfromjson.h"
#include "DartsController/DCPlayerServices/dcplayerkeys.h"
#include "DartsController/DCFinishesServices/dccreatefinishes.h"
#include "DartsController/DCFinishesServices/dclogisticdb.h"
#include "DartsController/DCScoresServices/dcresetscoremodels.h"
#include "DartsController/DCMetaServices/dcmetastatus.h"
#include "DartsController/DCMetaServices//dartsstatuscodes.h"
#include "DartsController/DCMetaServices/dchint.h"
#include "DartsController/DCMetaServices/dcinitialscore.h"
#include "DartsController/DCMetaServices/dctournamentid.h"
#include "DartsController/DPCServices/dpcinputvalidator.h"
#include "DartsController/DPCServices/dpcindexcontroller.h"
#include "DartsController/DPCServices/CreateDPCTurnValues.h"
#include "DartsController/DPCServices/dpcinputbuilder.h"
#include "DartsController/DPCServices/getscorefromdpcinput.h"
#include "DartsController/DPCServices/dpcinputstojson.h"
#include "DartsController/DPCServices/dpcinputstojson.h"
#include "DartsController/DPCServices/dpcindexestojson.h"
#include "DartsController/DCInputServices/DCInputKeyCodes.h"
#include "DartsController/DCJsonServices/dccreatebytearray.h"
#include "DartsController/DCJsonServices/dccreateemptyjsonobject.h"
#include "DartsController/DCTurnValuesServices/dcturnvaljsonkeys.h"
#include "DartsController/DCInputStatsServices/dcaveragecalc.h"
#include "DartsController/DCInputStatsServices/dcinputstatsavgkeys.h"
#include "DartsController/DCIndexServices/dcindexesjsonkeys.h"
#include "DartsController/DCPlayerServices/DPCPlayerAllowancesContext.h"
#include "DartsController/DCMetaServices/dcmetajsonbuilder.h"

class DPController : public DartsController
{
public:
    DPController(const DCBuilding::IDCMetaInfo *meta)
    {
        setIndexService(new DPCIndexController);
        setTurnValuesBuilder(new CreateDPCTurnValues);
        setCreateInputModelService(new DPCInputBuilder);
        setAddTotalScoresToJson(new AddTotalScoreToDartsInputsAsJson);
        setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(), DCLogisticDb::createInstance()));
        setDetermineStatusById(new DetermineStatusById);
        setGetTotalScoreService(new DCGetScoreCand);
        // Player services
        setPlayerAllowanceContext(new DPCPlayerAllowancesContext);
        setAddPlayerNamesToJson(new AddPlayerNamestoDartsInputsAsJson);
        // Meta services
        setControllerStatus(new DCMetaStatus);
        setStatusCodes(new DCStatusCodes);
        setDisplayHint(DCHint::createInstance(meta->displayHint()));
        setInputHint(DCHint::createInstance(meta->inputHint()));
        setTournamentId(DCTournamentId::createInstance(meta->tournamentId()));
        setInitialScore(DCInitialScore::createInstance(meta->keyPoint()));
        setSetMetaJsonValues(new DCMetaJsonBuilder);
        // Json services
        setInputJsonContext(new DPCInputsToJson);
        setTurnValuesToJsonService(new DCTurnValuesToJson);
        setIndexesToJsonService(new DPCIndexesToJson);
        setCreateByteArray(new DCCreateByteArray);
        setCreateEmptyJsonObject(new DCCreateEmptyJsonObject);
        // Scoremodels services
        setResetScoreModels(new DCResetScoreModels);
        setCreateScoreModelsService(new DCCreateScoreModels);
        setUpdateScoreModels(new DCUpdateScoreModels);
        setSubtractScore(new DCSubtractScore);
        setScoresService(new DCScoresService);
        setCreateCandidateTuples(new DCCreateCandidateModels);
        setWinnerService(new DCWinnerService);
        setAddScoreService(new DCAddScore);
        // Input services
        setInputKeyCodes(new DCInputKeyCodes);
        setInputEvaluator(DPCInputValidator::createInstance());
        setGetScoreFromInput(new GetScoreFromDPCInput);
        // Input statistics services
        setCalcInputAvg(new DCAverageCalc);
        setInputAvgKeys(new DCInputStatsAvgKeys);
        // Player services
        setPlayerBuilderService(new DCPlayerBuilder);
        setPlayerService(new DCPlayerService(indexService(),scoresService()));
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
        setIndexKeys(new DCIndexesJsonKeys);
        setIndexesBuilder(new DCIndexesBuilder);
        // TurnValues services
        setTurnValKeys(new DCTurnValJsonKeys);
    }
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
