#ifndef DSCONTROLLER_H
#define DSCONTROLLER_H
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DCScoresServices/dccreatescoremodels.h"
#include "DartsController/DCIndexServices/dcindexesbuilder.h"
#include "DartsController/DCIndexServices/dcindexredo.h"
#include "DartsController/DCPlayerServices/dcplayerservice.h"
#include "DartsController/DCIndexServices/dcresetindexes.h"
#include "DartsController/DCScoresServices/dcsubtractscore.h"
#include "DartsController/DCIndexServices/dcindexundo.h"
#include <quuid.h>
#include "DartsController/DCPlayerServices/dcwinnerkeys.h"
#include "DartsController/DCPlayerServices/dcplayerkeys.h"
#include "DartsController/DSCServices/dscindexcontroller.h"
#include "DartsController/DSCServices/dscinputvalidator.h"
#include "DartsController/DCMetaServices/dcwinnerservice.h"
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
#include "DartsController/DCInputStatsServices/dcaveragecalc.h"
#include "DartsController/DCIndexServices/dcindexesjsonkeys.h"
#include "DartsController/DCMetaServices/dcmetajsonbuilder.h"
#include "DartsControllerBuilder/DCBMetaServices/dcmeta.h"
#include "DartsController/DCJsonServices/dcjsonbuilder.h"
#include "DartsController/DCMetaServices/dcmetamodelbuilder.h"
class DSController : public DartsController
{
public:
    DSController(const DCBuilding::DCMeta &meta)
    {
        setWinnerService(new DCWinnerService());
        setTurnValuesBuilder(new DSCValuesBuilder);
        setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(),
                                                           DCLogisticDb::createInstance()));
        // Index services
        setInitializeIndexes(new DCInitializeIndexes);
        setIndexIterator(new DCIndexIterator);
        setResetIndexes(new DCResetIndexes);
        setUndoIndex(new DCIndexUndo);
        setRedoIndex(new DCIndexRedo);
        setIndexKeys(new DCIndexesJsonKeys);
        setIndexService(new DSCIndexController);
        setIndexesBuilder(new DCIndexesBuilder);
        // Scores services
        setCreateCandidateScores(new DCCreateCandidateModels);
        setGetTotalScoreService(new DCGetScoreCand);
        setScoresService(new DCScoresService);
        setScoreBuilder(new DCCreateScoreModels);
        setAddScoreService(new DCAddScore);
        // Meta services
        setDetermineStatusById(new DetermineStatusById);
        setControllerStatus(new DCMetaStatus);
        setStatusCodes(new DCStatusCodes);
        setDisplayHint(DCHint::createInstance(meta.displayHint));
        setInputHint(DCHint::createInstance(meta.inputHint));
        setTournamentId(DCTournamentId::createInstance(meta.tournamentId));
        setInitialScore(DCInitialScore::createInstance(meta.keyPoint));
        setSetMetaJsonValues(new DCMetaJsonBuilder);
        setMetaBuilder(new DCMetaModelBuilder(indexService(),scoresService()));
        // Json services
        setJsonResponseBuilder(new DCJsonBuilder);
        // Input services
        setGetScoreFromInput(new GetScoreFromDSCInput);
        setInputEvaluator(DSCInputValidator::createInstance());
        setInputBuilder(new DSCInputBuilder);
        // Input statistics services
        setCalcInputAvg(new DCAverageCalc);
        // Player score services
        setPlayerBuilderService(new DCPlayerBuilder);
        setSubtractScore(new DCSubtractScore);
        setUpdateScoreModels(new DCUpdateScoreModels);
        setResetScoreModels(new DCResetScoreModels);
        // Player services
        setPlayerService(new DCPlayerService);
        setWinnerModelFromJson(new DCGetWInnerModelsFromJson);
        setWinnerKeys(new DCWinnerKeys);
        setPlayerKeys(new DCPlayerKeys);

    }
};
#endif // DEFAULTDARTSSCORECONTROLLER_H
