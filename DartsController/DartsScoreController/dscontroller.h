#ifndef DSCONTROLLER_H
#define DSCONTROLLER_H
#include "DartsController/Controller/dartscontroller.h"
#include "DartsControllerBuilder/DCBMetaSLAs/idcmetainfo.h"
#include "DartsController/DCPlayerServices/dcplayerjsonbuilder.h"
#include "DartsController/DCScoresServices/dccreatescoremodels.h"
#include "DartsController/DCIndexServices/dcindexesbuilder.h"
#include "DartsController/DCIndexServices/dcindexredo.h"
#include "DartsController/DCPlayerServices/dcplayerservice.h"
#include "DartsController/DCIndexServices/dcresetindexes.h"
#include "DartsController/DCScoresServices/dcsubtractscore.h"
#include "DartsController/DCTurnValuesServices/dcturnvaluestojson.h"
#include "DartsController/DCIndexServices/dcindexundo.h"
#include <quuid.h>
#include "DartsController/DCPlayerServices/dcwinnerkeys.h"
#include "DartsController/DCPlayerServices/dccreateplayersfromjson.h"
#include "DartsController/DCPlayerServices/dcplayerkeys.h"
#include "DartsController/DSCServices/dscindexcontroller.h"
#include "DartsController/DSCServices/dscinputvalidator.h"
#include "DartsController/DCMetaServices/dcwinnerservice.h"
#include "DartsController/DSCServices/dscinputtojson.h"
#include "DartsController/DSCServices/dscinputbuilder.h"
#include "DartsController/DCMetaServices/determinestatusbyid.h"
#include "DartsController/DSCServices/dscvaluesbuilder.h"
#include "DartsController/DCPlayerServices/dcplayerbuilder.h"
#include "DartsController/DCScoresServices/dcscoresservice.h"
#include "DartsController/DCScoresServices/dcupdatescoremodels.h"
#include "DartsController/DCScoresServices/dccreatecandidatemodels.h"
#include "DartsController/DCScoresServices/dcaddscore.h"
#include "DartsController/DCScoresServices/dcgetscorecand.h"
#include "DartsController/DCIndexServices/dcinitializeindexservice.h"
#include "DartsController/DSCServices/getscorefromdscinput.h"
#include "DartsController/DSCServices/dscindexestojson.h"
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
#include "DartsController/DCInputServices/DCInputKeyCodes.h"
#include "DartsController/DCJsonServices/dccreatebytearray.h"
#include "DartsController/DCJsonServices/dccreateemptyjsonobject.h"
#include "DartsController/DCTurnValuesServices/dcturnvaljsonkeys.h"
#include "DartsController/DCInputStatsServices/dcaveragecalc.h"
#include "DartsController/DCIndexServices/dcindexesjsonkeys.h"
#include "DartsController/DCMetaServices/dcmetajsonbuilder.h"
class DSController : public DartsController
{
public:
    DSController(const DCBuilding::IDCMetaInfo *meta)
    {
        setIndexService(new DSCIndexController);
        setWinnerService(new DCWinnerService());
        setTurnValuesBuilder(new DSCContext::DSCValuesBuilder);
        setInputBuilder(new DSCInputBuilder);
        setIndexesBuilder(new DCIndexesBuilder);
        setCreateCandidateTuples(new DCCreateCandidateModels);
        setPlayerBuilderService(new DCPlayerBuilder);
        setDetermineStatusById(new DetermineStatusById);
        setScoresService(new DCScoresService);
        setAddScoreService(new DCAddScore);
        setGetTotalScoreService(new DCGetScoreCand);
        setCreateScoreModelsService(new DCCreateScoreModels);
        setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(), DCLogisticDb::createInstance()));
        // Meta services
        setControllerStatus(new DCMetaStatus);
        setStatusCodes(new DCStatusCodes);
        setDisplayHint(DCHint::createInstance(meta->displayHint()));
        setInputHint(DCHint::createInstance(meta->inputHint()));
        setTournamentId(DCTournamentId::createInstance(meta->tournamentId()));
        setInitialScore(DCInitialScore::createInstance(meta->keyPoint()));
        setSetMetaJsonValues(new DCMetaJsonBuilder);
        // Json services
        setTurnValuesToJsonService(new DCTurnValuesToJson);
        setCreateByteArray(new DCCreateByteArray);
        setCreateEmptyJsonObject(new DCCreateEmptyJsonObject);
        // Input services
        setInputJsonContext(new DSCInputToJson);
        setGetScoreFromInput(new GetScoreFromDSCInput);
        setInputKeyCodes(new DCInputKeyCodes);
        setInputEvaluator(DSCInputValidator::createInstance());
        // Input statistics services
        setCalcInputAvg(new DCAverageCalc);
        // Player score services
        setSubtractScore(new DCSubtractScore);
        setUpdateScoreModels(new DCUpdateScoreModels);
        setResetScoreModels(new DCResetScoreModels);
        // Player services
        setPlayerService(new DCPlayerService(indexService(),scoresService()));
        setWinnerModelFromJson(new DCGetWInnerModelsFromJson);
        setCreateJsonFromPlayer(new DCPlayerJsonBuilder);
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
        setIndexKeys(new DCIndexesJsonKeys);
        // Turnvalues services
        setTurnValKeys(new DCTurnValJsonKeys);
    }
};
#endif // DEFAULTDARTSSCORECONTROLLER_H
